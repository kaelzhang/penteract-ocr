#include <nan.h>
#include <stdint.h>
#include "fromFile.h"
#include "recognize.h"


using Nan::New;
using Nan::Set;
using v8::String;
using v8::FunctionTemplate;

NAN_MODULE_INIT(Init) {
  Set(target,
      New<String>("fromFile").ToLocalChecked(),
      New<FunctionTemplate>(FromFile)->GetFunction());

  Set(target,
      New<String>("recognize").ToLocalChecked(),
      New<FunctionTemplate>(Recognize)->GetFunction());
}


NODE_MODULE(penteract, Init);
