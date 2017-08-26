#include <node_api.h>
#include <assert.h>
#include <stdint.h>
#include "ocr.h"


napi_value
_recognizePix (napi_env env, Pix *image, const char *lang) {
  napi_status status;

  char *outText = nullptr;
  char *error_code = nullptr;
  char *error_message = nullptr;
  int tess_failed = TessRecognizePix(image, lang, outText, NULL,
                                     error_code, error_message);

  pixDestroy(&image);

  if (tess_failed) {
    napi_throw_type_error(env, error_code, error_message);
    return nullptr;
  }

  napi_value returnValue;
  status = napi_create_string_utf8(env, outText, strlen(outText), &returnValue);
  delete [] outText;

  assert(status == napi_ok);
  return returnValue;
}


// JavaScript API:
// penteract.fromFile(filepath: String, lang: String) : String

napi_value
FromFile(napi_env env, napi_callback_info info) {
  napi_status status;

  // Arguments
  /////////////////////////////////////////////////////////////////////////////
  size_t argc = 2;
  napi_value args[2];
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 2) {
    napi_throw_type_error(env, "WRONG_ARG_LENGTH", "Wrong number of arguments");
    return nullptr;
  }

  napi_valuetype valuetype_filepath;
  status = napi_typeof(env, args[0], &valuetype_filepath);
  assert(status == napi_ok);

  napi_valuetype valuetype_lang;
  status = napi_typeof(env, args[1], &valuetype_lang);
  assert(status == napi_ok);

  if (valuetype_filepath != napi_string) {
    napi_throw_type_error(env, "INVALID_PATH", "path must be a string.");
    return nullptr;
  }

  if (valuetype_lang != napi_string) {
    napi_throw_type_error(env, "INVALID_LANG", "lang must be a string.");
    return nullptr;
  }

  size_t size_written, size_filepath, size_lang;

  status = napi_get_value_string_utf8(env, args[0], NULL, 0, &size_filepath);
  ++ size_filepath;
  char *filepath = new char[size_filepath];
  status = napi_get_value_string_utf8(env, args[0], filepath, size_filepath,
                                      &size_written);
  assert(status == napi_ok);

  status = napi_get_value_string_utf8(env, args[1], NULL, 0, &size_lang);
  ++ size_lang;
  char *lang = new char[size_lang];
  status = napi_get_value_string_utf8(env, args[1], lang, size_lang,
                                      &size_written);
  assert(status == napi_ok);

  // OCR
  /////////////////////////////////////////////////////////////////////////////

  // Open input image with leptonica library
  Pix *image = pixRead(filepath);

  return _recognizePix(env, image, lang);
}


napi_value
Recognize(napi_env env, napi_callback_info info) {
  napi_status status;

  // Arguments
  /////////////////////////////////////////////////////////////////////////////
  size_t argc = 2;
  napi_value args[2];
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 2) {
    napi_throw_type_error(env, "WRONG_ARG_LENGTH", "Wrong number of arguments");
    return nullptr;
  }

  bool valuetype_is_buffer;
  status = napi_is_buffer(env, args[0], &valuetype_is_buffer);
  assert(status == napi_ok);

  napi_valuetype valuetype_lang;
  status = napi_typeof(env, args[1], &valuetype_lang);
  assert(status == napi_ok);

  if (!valuetype_is_buffer) {
    napi_throw_type_error(env, "INVALID_BUFFER", "the first argument only accepts a Buffer.");
    return nullptr;
  }

  if (valuetype_lang != napi_string) {
    napi_throw_type_error(env, "INVALID_LANG", "lang must be a string.");
    return nullptr;
  }


  // buffer
  size_t size_buffer;
  uint8_t *buffer;
  status = napi_get_buffer_info(env, args[0], (void**)(&buffer), &size_buffer);
  assert(status == napi_ok);

  // lang
  size_t size_written, size_lang;
  status = napi_get_value_string_utf8(env, args[1], NULL, 0, &size_lang);
  ++ size_lang;
  char *lang = new char[size_lang];
  status = napi_get_value_string_utf8(env, args[1], lang, size_lang,
                                      &size_written);
  assert(status == napi_ok);

  Pix *image = pixReadMem(buffer, size_buffer);

  return _recognizePix(env, image, lang);
}


#define DECLARE_NAPI_METHOD(name, func)  \
  { name, 0, func, 0, 0, 0, napi_default, 0 }


void
Init(napi_env env, napi_value exports, napi_value module, void* priv) {
  napi_status status;

  napi_property_descriptor from_file_desc = DECLARE_NAPI_METHOD("fromFile", FromFile);
  status = napi_define_properties(env, exports, 1, &from_file_desc);
  assert(status == napi_ok);

  napi_property_descriptor recognize_desc = DECLARE_NAPI_METHOD("recognize", Recognize);
  status = napi_define_properties(env, exports, 1, &recognize_desc);
  assert(status == napi_ok);
}


NAPI_MODULE(penteract, Init);
