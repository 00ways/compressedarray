cmake_minimum_required(VERSION 3.16)

project(compressedarray LANGUAGES C)

add_library(compressedarray
    src/compressedarray.c
    src/textutil.c)
target_include_directories(compressedarray PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
