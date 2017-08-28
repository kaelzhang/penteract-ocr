#include <nan.h>
#include "fromFile.h"
#include "ocr.h"
#include "AsyncWorker.h"


using Nan::Callback;
using Nan::HandleScope;
using Nan::AsyncQueueWorker;


class FromFileWorker : public PenteractWorker {

private:
  char *filepath_;

  Pix* ReadImage () {
    return pixRead(filepath_);
  }

public:
  FromFileWorker (char *filepath,
                  char *lang,
                  Callback *callback)
    : PenteractWorker(lang, callback), filepath_(nullptr) {

      SetChar(&filepath_, filepath);
    }

  ~FromFileWorker () {
    HandleScope scope;
    delete[] filepath_;
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
