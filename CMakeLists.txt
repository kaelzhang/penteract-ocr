#
# penteract
#

cmake_minimum_required(VERSION 3.7)
project(penteract)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cc/AsyncWorker.h
        cc/fromFile.cc
        cc/fromFile.h
        cc/ocr.cc
        cc/ocr.h
        cc/penteract.cc
        cc/recognize.cc
        cc/recognize.h)

#add_executable(napi_penteract ${SOURCE_FILES})