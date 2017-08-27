#include <nan.h>
#include "fromFile.h"
#include "ocr.h"

using Nan::New;

// JavaScript API:
// penteract.fromFile(filepath: String, lang: String) : String

NAN_METHOD(FromFile) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsString() || !info[1]->IsString()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  // Open input image with leptonica library
  Pix *image = pixRead(*v8::String::Utf8Value(info[0]));

  char *outText = nullptr;
  char *error_code = nullptr;
  char *error_message = nullptr;
  int tess_failed = TessRecognizePix(image, *v8::String::Utf8Value(info[1]),
                                     outText, NULL,
                                     error_code, error_message);

  if (tess_failed) {
    Nan::ThrowError(error_message);
    return;
  }

  info.GetReturnValue()
      .Set(New(outText, strlen(outText)).ToLocalChecked());

  delete [] outText;
}
