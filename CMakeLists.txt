cmake_minimum_required(VERSION 2.8)
project(linepass)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_BUILD_TYPE "Debug")

add_subdirectory(linepassd)
add_subdirectory(linepassc)
