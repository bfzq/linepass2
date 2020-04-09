include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/line)

set(LINE ${CMAKE_SOURCE_DIR}/line)

add_executable(linepassc
linec_main.cc
main.cc)
