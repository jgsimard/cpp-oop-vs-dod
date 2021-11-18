cmake_minimum_required(VERSION 3.16)
project(cpp_oop_vs_dod)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_executable(cpp_oop_vs_dod main.cpp Node.cpp Node.h)

add_executable(simple_benchmark simple_benchmark.cpp)
