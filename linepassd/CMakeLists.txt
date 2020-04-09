include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/line)

set(LINE ${CMAKE_SOURCE_DIR}/line)

add_executable(linepassd
lined_main.cc
${LINE}/line_args.cc
${LINE}/line_log.cc
lined_args.cc
lined_net.cc
${LINE}/lepoll.cc
main.cc)
