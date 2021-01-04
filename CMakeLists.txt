cmake_minimum_required(VERSION 3.10)
project(basic_raytracer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    include/
)

add_subdirectory(src)
