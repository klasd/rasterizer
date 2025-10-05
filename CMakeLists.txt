cmake_minimum_required(VERSION 4.0)
project(rasterizer C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS} src)
link_directories(${SDL2_LIBRARY_DIRS})

add_executable(rasterizer
        src/display.c
        src/display.h
        src/main.c
        src/vec2.c
        src/vec2.h
)

target_link_libraries(rasterizer ${SDL2_LIBRARIES} m)
