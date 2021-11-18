//
// base on this : https://github.com/nxrighthere/DataBenchmark/blob/master/DataBenchmark.cpp
//

#include <iostream>
#include <chrono>
#include <memory>
#include <functional>

#define ITERATION_COUNT 1000000

struct Object {
    int a;
    int b;
    int c;

    int Foo() {
        return a + b + c;
    }
};

struct FragmentedObject {
    int a;
    char f1[64];
    int b;
    char f2[128];
    int c;
    char f3[256];
    int d;

    int Foo() {
        d = a + b + c;
        return d;
    }
};

struct DerivedObject : Object {
    char o1[64];
    char o2[128];
    char o3[256];
};

int Foo(int a, int b, int c) {
    return a + b + c;
}


int time_it_n(std::function<int()> const &f) {
    auto start = std::chrono::high_resolution_clock::now();
    int n = 0;
    int N = 100;
    for (int i = 0; i < N; i++) {
        n = f();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / N;
//    std::cout << n << std::endl; // just to make sure the funciton is not removed by the optimization
    return duration;
}


int main() {
    auto a = new int[ITERATION_COUNT];
    auto b = new int[ITERATION_COUNT];
    auto c = new int[ITERATION_COUNT];
    auto o = new struct Object[ITERATION_COUNT];
    auto f = new struct FragmentedObject[ITERATION_COUNT];
    auto d = new struct DerivedObject[ITERATION_COUNT];

    // DOD
    auto dod = [&]() {
        auto n = 0;
        for (int i = 0; i < ITERATION_COUNT; ++i) {
            n += Foo(a[i], b[i], c[i]);
        }
        return n;
    };
    std::cout << time_it_n(dod) << " (DOD,  perfect utilization)" << std::endl;

    // OOD
    auto ood = [&]() {
        int n = 0;
        for (int i = 0; i < ITERATION_COUNT; ++i) {
            n += o[i].Foo();
        }
        return n;
    };
    std::cout << time_it_n(ood) << " (OOD,  perfect utilization)" << std::endl;

    // OOD (fragmented)
    auto ood_fragmented = [&]() {
        int n = 0;
        for (int i = 0; i < ITERATION_COUNT; ++i) {
            n += f[i].Foo();
        }
        return n;
    };
    std::cout << time_it_n(ood_fragmented) << " (OOD, fragmented utilization)" << std::endl;

    // OOP (Inheritance)
    auto ood_inheritance = [&]() {
        int n = 0;
        for (int i = 0; i < ITERATION_COUNT; ++i) {
            n += d[i].Foo();
        }
        return n;
    };
    std::cout << time_it_n(ood_inheritance) << " (OOD, derived utilization)" << std::endl;

    delete[] a;
    delete[] b;
    delete[] c;
    delete[] o;
    delete[] f;
    delete[] d;
}
