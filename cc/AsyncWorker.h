#ifndef __PENTERACT_ASYNC_WORKER_H__
#define __PENTERACT_ASYNC_WORKER_H__

#include <nan.h>
#include <leptonica/allheaders.h>


using Nan::New;
using Nan::HandleScope;
using Nan::Null;
using Nan::AsyncWorker;
using Nan::Callback;


// Abstract
class PenteractWorker : public AsyncWorker {

private:
  char *errcode_;

protected:

  char *outText;
  char *lang;

  // Set a char
  inline void SetChar (char **receiver, const char *provider) {
    delete[] *receiver;
    size_t size = strlen(provider) + 1;
    *receiver = new char[size];
    memcpy(*receiver, provider, size);
  }

  // Set lang
  void SetLang (const char *l) {
    SetChar(&lang, l);
  }

  // Set error code and error message
  void SetError (const char *code, const char *msg) {
    SetChar(&errcode_, code);
    SetErrorMessage(msg);
  }

  const char* ErrorCode () const {
    return errcode_;
  }

  void HandleErrorCallback() {
    HandleScope scope;

    v8::Local<v8::Value> argv[] = {
      New<v8::String>(ErrorCode()).ToLocalChecked(),
      New<v8::String>(ErrorMessage()).ToLocalChecked()
    };
    callback->Call(2, argv);
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

  virtual Pix* ReadImage () = 0;

public:
  PenteractWorker (char *lang, Callback *callback)
    : AsyncWorker(callback),
      errcode_(nullptr),
      lang(nullptr) {

      SetLang(lang);
    }

  virtual ~PenteractWorker () {
    HandleScope scope;
    delete[] errcode_;
    delete[] lang;
  }

  void Execute () {
    Pix *image = ReadImage();

    if (image == nullptr) {
      SetError("ERR_READ_IMAGE", "Fails to read image.");
      return;
    }

    char *error_code = nullptr;
    char *error_message = nullptr;
    int tess_failed = TessRecognizePix(image, lang,
                                       outText, nullptr,
                                       error_code, error_message);

    if (tess_failed) {
      SetError(error_code, error_message);
      return;
    }
  }
};


#endif
