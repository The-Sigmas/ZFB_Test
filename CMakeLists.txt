cmake_minimum_required(VERSION 3.10)
project(ZFB_Test C)

add_executable(zfbTest src/main.c)

target_include_directories(zfbTest PRIVATE /c/git/ZFB/src/headers)
target_link_directories(zfbTest PRIVATE /c/git/ZFB/build/lib)

include_directories(/c/msys64/mingw64/include/libpng16)
link_directories(/c/msys64/mingw64/lib)

target_link_libraries(zfbTest PRIVATE ZFB gdi32 png16)
