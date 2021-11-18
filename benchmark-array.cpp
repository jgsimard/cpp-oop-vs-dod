//
// Created by jeang on 2021-11-18.
// This is a reimplementation of http://jamesmcm.github.io/blog/2020/07/25/intro-dod/#en
// to better understand DOD vs OOP
//
#include <string>
#include <utility>      // std::pair, std::make_pair
#include <vector>
#include <random>
#include <functional> // std::bind
#include <iostream>
#include <iomanip>

#include "utils.h"

using std::cout;
using std::endl;
using std::vector;
using std::pair;

// Object Oriented Programming
struct Player {
    std::string name;
    float health;
    pair<double, double> location;
    pair<double, double> velocity;
    pair<double, double> acceleration;
};

void run_oop(std::vector<Player>& players){
    for(auto& player: players){
        // update location
        player.location.first += player.velocity.first;
        player.location.second += player.velocity.second;
        // update velocity
        player.velocity.first += player.acceleration.first;
        player.velocity.second += player.acceleration.second;
    }
}

vector<Player> generate_oop(int size){
    double temp = 2.3;
    vector<Player> players(size, Player{
            .name = "player_name_" ,
            .health = 100.0,
            .location = std::make_pair(temp, temp),
            .velocity = std::make_pair(temp, temp),
            .acceleration = std::make_pair(temp, temp)
    });
    return players;
}

// Data Oriented Programming
struct DataOrientedPlayers {
    vector<std::string> names;
    vector<float> health;
    vector<pair<double, double>> locations;
    vector<pair<double, double>> velocities;
    vector<pair<double, double>> accelerations;
};

void run_dop(DataOrientedPlayers& players){
    unsigned n = players.names.size();
    for(unsigned i = 0; i < n; ++i){
        // update location
        players.locations[i].first += players.velocities[i].first;
        players.locations[i].second += players.velocities[i].second;
        // update velocity
        players.velocities[i].first += players.accelerations[i].first;
        players.velocities[i].second += players.accelerations[i].second;
    }
}

DataOrientedPlayers generate_dop(unsigned size){
    double t = 2.3;
    return DataOrientedPlayers {
            .names = vector<std::string>(size, "player_name_"),
            .health = vector<float>(size, 100),
            .locations = vector<pair<double, double>>(size, std::make_pair(t, t)),
            .velocities = vector<pair<double, double>>(size, std::make_pair(t, t)),
            .accelerations = vector<pair<double, double>>(size, std::make_pair(t, t)),
    };
}

void benchmark_struct_of_arrays(){
    cout << "Array of struct (OOP) VS Struc of Array (DOP)" << endl;
    vector<unsigned> sizes{100, 1000, 10000, 100000, 1000000, 3000000, 5000000, 10000000};
//    std::vector<unsigned> sizes{100, 1000, 10000, 100000, 1000000, 10000000};
//    std::vector<unsigned> sizes{100, 1000, 10000, 100000, 1000000};
    std::cout << std::setw(10) << "size" << std::setw(14) << "oop_time (us)"<< std::setw(14) << "dop_time (us)"<< std::endl;
    for(int size: sizes){
        // oop
        auto oop_input = generate_oop(size);
        int oop_time = time_it(std::bind(run_oop, oop_input));
        // dop
        auto dop_input = generate_dop(size);
        int dop_time = time_it(std::bind(run_dop, dop_input));
        // print
        std::cout  << std::setw(10) << size
                   << std::setw(14) << oop_time
                   << std::setw(14) << dop_time << std::endl;

    }
//    for(int size: sizes){
//        // oop
//        int oop_time = time_it(std::bind(generate_oop, size));
//        // dop
//        int dop_time = time_it(std::bind(generate_dop, size));
//        // print
//        std::cout  << std::setw(10) << size
//                   << std::setw(10) << oop_time
//                   << std::setw(10) << dop_time << std::endl;
//    }
}
int main(){
    benchmark_struct_of_arrays();
}


