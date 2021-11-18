//
// Created by jeang on 2021-11-18.
// This is a reimplementation of http://jamesmcm.github.io/blog/2020/07/25/intro-dod/#en
// to better understand DOD vs OOP
//
#include <random>
#include <string>
#include <utility>      // std::pair, std::make_pair
#include <vector>
#include <random>
#include <functional> // std::bind
#include <iostream>
#include <iomanip>
#include <iterator>
#include <tuple>
#include <algorithm> //random_shuffle

#include "utils.h"

using std::cout;
using std::endl;
using std::vector;
using std::pair;

enum class CalcType{
    Identity,
    Square,
    Cube
};
struct Foo{
    int x;
    CalcType calc_type;
};

// Object Oriented Programming
std::tuple<vector<Foo>, vector<Foo>, vector<Foo>> generate_separated(unsigned size){
    vector<Foo> x(size/3, Foo{.x = 1, .calc_type = CalcType::Identity});
    vector<Foo> y(size/3, Foo{.x = 1, .calc_type = CalcType::Square});
    vector<Foo> z(size/3, Foo{.x = 1, .calc_type = CalcType::Cube});
    return std::make_tuple(x,y,z);
}

vector<Foo> generate_mixed(unsigned size){
    auto[x,y,z] = generate_separated(size);
    x.insert(x.end(), std::make_move_iterator(y.begin()), std::make_move_iterator(y.end()));
    x.insert(x.end(), std::make_move_iterator(z.begin()), std::make_move_iterator(z.end()));
    std::shuffle(x.begin(), x.end(), std::mt19937(std::random_device()()));
    return x;
}

void run_mixed(vector<Foo> input){
    input[0].x =std::accumulate(input.begin(), input.end(), 0, [](int acc,const Foo& foo){
        switch (foo.calc_type) {
            case CalcType::Cube: return acc + foo.x * foo.x * foo.x; break;
            case CalcType::Square: return acc + foo.x * foo.x; break;
            case CalcType::Identity: return acc + foo.x; break;
            default: return acc + foo.x;
        }});
}

void run_separated(vector<Foo> x, vector<Foo> y, vector<Foo> z){
    x[0].x = std::accumulate(x.begin(), x.end(), 0, [](int acc, const Foo& foo){ return acc + foo.x;})
    + std::accumulate(y.begin(), y.end(), 0, [](int acc, const Foo& foo){ return acc + foo.x * foo.x;})
    + std::accumulate(z.begin(), z.end(), 0, [](int acc, const Foo& foo){ return acc + foo.x * foo.x * foo.x;});
}
// Data Oriented Programming


void benchmark_branching(){
    cout << "Mixed array VS Separated Array (DOP)" << endl;
    std::vector<unsigned> sizes{100, 1000, 10000, 100000, 1000000, 10000000};
    std::cout << std::setw(10) << "size" << std::setw(14) << "mixed (us)"<< std::setw(14) << "separated (us)"<< std::endl;
    for(int size: sizes){
        // oop
        auto mixed_input = generate_mixed(size);
        int mixed_time = time_it(std::bind(run_mixed, mixed_input));
        // dop
        auto [x,y,z] = generate_separated(size);
        int separated_time = time_it(std::bind(run_separated, x,y,z));
        // print
        std::cout  << std::setw(10) << size
                   << std::setw(14) << mixed_time
                   << std::setw(14) << separated_time << std::endl;

    }
}



