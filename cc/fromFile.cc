#include <nan.h>
#include "fromFile.h"
#include "ocr.h"

using Nan::New;
using Nan::Callback;
using Nan::HandleScope;
using Nan::Null;
using Nan::AsyncWorker;
using Nan::AsyncQueueWorker;


class FromFileWorker : public AsyncWorker {

private:
  char *outText;
  char *filepath = nullptr;
  char *lang = nullptr;

  void SetFilepath (const char *f) {
    delete[] filepath;
    size_t size = strlen(f) + 1;
    filepath = new char[size];
    memcpy(filepath, f, size);
  }

  void SetLang (const char *l) {
    delete[] lang;
    size_t size = strlen(l) + 1;
    lang = new char[size];
    memcpy(lang, l, size);
  }

public:
  FromFileWorker (char *filepath,
                  char *lang,
                  Callback *callback)
    : AsyncWorker(callback) {

      SetFilepath(filepath);
      SetLang(lang);
    }

  ~FromFileWorker () {}

  void Execute () {
    Pix *image = pixRead(filepath);

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


// JavaScript API:
// penteract.fromFile(filepath: String, lang: String, callback: Function)

NAN_METHOD(FromFile) {
  AsyncQueueWorker(new FromFileWorker(
    // filepath
    *v8::String::Utf8Value(info[0]),
    // lang
    *v8::String::Utf8Value(info[1]),
    // callback
    new Callback(info[2].As<v8::Function>())
  ));
}
