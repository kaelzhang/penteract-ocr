#ifndef __PENTERACT_OCR_H__
#define __PENTERACT_OCR_H__

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


int TessRecognizePix (Pix *image,
                      const char *lang, char *&outText, const char *datapath,
                      char *error_code, char *error_message);

#endif
