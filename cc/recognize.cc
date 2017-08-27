#include <nan.h>
#include <stdint.h>
#include "recognize.h"
#include "ocr.h"

using Nan::New;
using Nan::Callback;
using Nan::HandleScope;
using Nan::Null;
using Nan::AsyncWorker;
using Nan::AsyncQueueWorker;


class RecognizeWorker : public AsyncWorker {

private:
  char *outText;
  uint8_t *buffer;
  size_t length;
  char *lang = nullptr;

  void SetLang (const char *l) {
    delete[] lang;
    size_t size = strlen(l) + 1;
    lang = new char[size];
    memcpy(lang, l, size);
  }

public:
  RecognizeWorker (uint8_t *buffer,
                  size_t length,
                  char *lang,
                  Callback *callback)
    : AsyncWorker(callback), buffer(buffer), length(length) {

      SetLang(lang);
    }

  ~RecognizeWorker () {}

  void Execute () {
    printf("%zu", length);
    Pix *image = pixReadMem(buffer, length);

    char *error_code = nullptr;
    char *error_message = nullptr;
    int tess_failed = TessRecognizePix(image, lang,
                                       outText, NULL,
                                       error_code, error_message);

    if (tess_failed) {
      SetErrorMessage(error_message);
      return;
    }
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback () {
    HandleScope scope;

    v8::Local<v8::Value> argv[] = {
      Null(),
      New(outText, strlen(outText)).ToLocalChecked()
    };

    callback->Call(2, argv);
  }
};


// Ref:
// https://github.com/nodejs/node/blob/master/src/node_api.cc#L2911
void
_getBufferInfo(v8::Local<v8::Object> buffer,
               void** data,
               size_t* length) {

  if (data != nullptr) {
    *data = node::Buffer::Data(buffer);
  }

  if (length != nullptr) {
    *length = node::Buffer::Length(buffer);
  }
}


// JavaScript API:
// penteract.fromFile(buffer: Buffer, lang: String, callback: Function)

NAN_METHOD(Recognize) {

  size_t bufferLength;
  uint8_t *bufferData;

  _getBufferInfo(info[0]->ToObject(), (void**)(&bufferData), &bufferLength);

  AsyncQueueWorker(new RecognizeWorker(
    // buffer
    bufferData,
    bufferLength,
    // lang
    *v8::String::Utf8Value(info[1]),
    // callback
    new Callback(info[2].As<v8::Function>())
  ));
}
