cmake_minimum_required(VERSION 3.3)
project(Image)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Img.cpp Img.h)
add_executable(Image ${SOURCE_FILES})