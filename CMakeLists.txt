cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(ZFB_DIR /home/bombacat/git/ZFB)

include_directories(${ZFB_DIR}/src/headers)

link_directories(${ZFB_DIR}/build/lib)

add_executable(myapp src/main.c)

target_link_libraries(myapp ZFB png)
