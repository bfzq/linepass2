cmake_minimum_required(VERSION 3.13)
project(linepassc)
set(CMAKE_CXX_STANDARD 11)
add_executable(linepassd
        linepassd/lined_main.cc
        linepassd/main.cc)
add_executable(linepassc
        linepassc/linec_main.cc
        linepassc/main.cc)