cmake_minimum_required(VERSION 3.13)
project(linepassc)
set(CMAKE_CXX_STANDARD 11)
include_directories(line_com)
add_executable(linepassd
        linepassd/lined_main.cc
        line_com/line_args.cc
	line_com/line_log.cc
        linepassd/lined_args.cc
        linepassd/main.cc)
add_executable(linepassc
        linepassc/linec_main.cc
        linepassc/main.cc)
