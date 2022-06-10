cmake_minimum_required(VERSION 3.18)

project(mgfx-workspace)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_subdirectory(extern)
add_subdirectory(mgfx)
add_subdirectory(examples)
