//
// Created by jeang on 2021-11-18.
//

#ifndef CPP_OOP_VS_DOD_UTILS_H
#define CPP_OOP_VS_DOD_UTILS_H

#include <chrono>
#include <functional>


int time_it(std::function<void()> const &f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    return duration;
}

int time_it_n(std::function<void()> const &f, unsigned n) {
    auto start = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < n; ++i) {
        f();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    return duration / n;
}

#endif //CPP_OOP_VS_DOD_UTILS_H
