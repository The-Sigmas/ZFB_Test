cmake_minimum_required(VERSION 3.10)
project(ZFB_Test)

set(ZFB_DIR ~/ZFB)

include_directories(${ZFB_DIR}/src/headers)

link_directories(${ZFB_DIR}/build/lib)

add_executable(zfbTest src/main.c)

target_link_libraries(zfbTest ZFB png)
