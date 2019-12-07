cmake_minimum_required(VERSION 3.15)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(ray_tracer main.cpp headers/vect.h headers/object.h headers/color.h headers/ray.h src/object.cpp headers/scene.h src/scene.cpp)