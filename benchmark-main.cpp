//
// Created by jeang on 2021-11-18.
// This is a reimplementation of http://jamesmcm.github.io/blog/2020/07/25/intro-dod/#en
// to better understand DOD vs OOP
//

#include <iostream>
#include "benchmark/benchmark-array.hpp"
#include "benchmark/benchmark-branching.hpp"

using std::cout;
using std::endl;

int main(){
    benchmark_struct_of_arrays();
    benchmark_branching();
}


