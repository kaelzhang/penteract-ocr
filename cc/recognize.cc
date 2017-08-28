#include <nan.h>
#include <stdint.h>
#include "recognize.h"
#include "ocr.h"
#include "AsyncWorker.h"


using Nan::Callback;
using Nan::HandleScope;
using Nan::AsyncQueueWorker;


class RecognizeWorker : public PenteractWorker {

private:
  uint8_t *buffer;
  size_t length;

  Pix* ReadImage () {
    return pixReadMem(buffer, length);
  }

public:
  RecognizeWorker (uint8_t *buffer,
                  size_t length,
                  char *lang,
                  Callback *callback)
    : PenteractWorker(lang, callback), buffer(buffer), length(length) {}

  ~RecognizeWorker () {}
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
