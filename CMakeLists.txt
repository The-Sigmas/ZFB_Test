cmake_minimum_required(VERSION 3.13)
project(ZFB_Test C)

add_executable(zfbTest src/main.c)

target_include_directories(zfbTest PUBLIC /c/git/ZFB/src/headers)

target_link_libraries(zfbTest PRIVATE /c/git/ZFB/build/lib/libZFB_C.a gdi32)
