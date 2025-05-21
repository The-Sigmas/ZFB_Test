cmake_minimum_required(VERSION 3.13)
project(ZFB_Test C)

set(ZFB_DIR /home/bombacat/git/ZFB)

add_executable(zfbTest src/main.c)

target_include_directories(zfbTest PRIVATE ${ZFB_DIR}/src/headers/)

target_link_libraries(zfbTest PRIVATE ${ZFB_DIR}/build/lib/libZFB_C.a m)
