#include <nan.h>
#include <stdint.h>
#include "fromFile.h"


using Nan::New;
using Nan::Set;
using v8::String;
using v8::FunctionTemplate;

NAN_MODULE_INIT(Init) {
  Set(target,
      New<String>("fromFile").ToLocalChecked(),
      New<FunctionTemplate>(FromFile)->GetFunction());

  // exports->Set(New("recognize").ToLocalChecked(),
  //              New<v8::FunctionTemplate>(Recognize)->GetFunction());
}


NODE_MODULE(penteract, Init);
