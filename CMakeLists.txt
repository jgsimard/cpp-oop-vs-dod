cmake_minimum_required(VERSION 3.16)
project(cpp_oop_vs_dod)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
#set(CMAKE_CXX_FLAGS "-Ofast -Wall -Wextra")
#set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native") # for SSE and AVX

include_directories(
        include
)
add_executable(cpp_oop_vs_dod
        main.cpp
        Node.cpp
        Node.h
        benchmark-array.cpp
)

add_executable(simple_benchmark
        simple_benchmark.cpp
)


add_executable(benchmark
        benchmark-array.cpp
)
