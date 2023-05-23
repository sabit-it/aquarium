#pragma once

#include "predator.h"
#include "../../constants/defines.h"
#include <chrono>
#include <random>
#include <vector>
#include <string>

struct predator;

struct fish {

    explicit fish(int cur_x = -1, int cur_y = -1) {
        if(cur_x == -1 && cur_y == -1){
            life_start = std::chrono::steady_clock::now();
            std::random_device rd;
            std::mt19937 gen(rd());

            std::uniform_int_distribution<> dis(100, 1720);
            x = dis(gen);

            std::uniform_int_distribution<> dis_y(100, 780);
            y = dis_y(gen);

            std::uniform_int_distribution<> fish_type(1, 2);
            type = fish_type(gen);
        }
    }

    int path_count = 0;

    float hungry_level = 60;
    int age = 0;
    float x, y;


    int type = 1;


    float predator_x = 0;
    float predator_y = 0;
    float distance_predator = 1e9;

    float move_x = 0;
    float move_y = 0;

    float angle = 0;
    float angle_destination = 0;

    bool destination_right = true;

    bool is_alive = true;


    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> life_start;


    bool find_predator(std::vector<predator>& predators);

    void move(std::vector<predator>& predators);

    void set_rotation();

};

void move_fishes(std::vector<fish>& fishes, std::vector<predator>& p);
