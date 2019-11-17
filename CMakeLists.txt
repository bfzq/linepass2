# cmake_minimum_required(VERSION 3.13)
project(linepassc)
set(CMAKE_CXX_STANDARD 13)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_BUILD_TYPE "Debug")	
include_directories(line_com)
add_executable(linepassd
        linepassd/lined_main.cc
        line_com/line_args.cc
	line_com/line_log.cc
        linepassd/lined_args.cc
	linepassd/lined_net.cc
	line_com/lepoll.cc
        linepassd/main.cc)
add_executable(linepassc
        linepassc/linec_main.cc
        linepassc/main.cc)
