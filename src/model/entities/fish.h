#pragma once

#include "predator.h"
#include "../../constants/defines.h"
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include "../../domain/actionc.h"

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

        if(type == 1) {
            width = FIRST_FISH_WIDTH;
            height = FIRST_FISH_HEIGHT;
        } else {
            width = SECOND_FISH_WIDTH;
            height = SECOND_FISH_HEIGHT;
        }
    }

    COORD eye_cord;
    COORD inner_eye;

    int path_count = 0;

    float hungry_level = 60;
    int age = 0;
    float x, y;


    int type = 1;

    float width;
    float height;

    float predator_x = 0;
    float predator_y = 0;
    float distance_predator = 1e9;

    float closest_predator_x;
    float closest_predator_y;
    float move_x = 0;
    float move_y = 0;

    float angle = 0;
    float angle_destination = 0;

    bool destination_right = true;

    bool is_alive = true;
    bool predator_found = false;
    bool is_first = true;

    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> start_run;
    std::chrono::time_point<std::chrono::steady_clock> life_start;

    bool found_close_predator = false;
    bool find_predator(std::vector<predator>& predators);

    void move(std::vector<predator>& predators);

    void set_rotation();

    void run_set_rotation();

};

void move_fishes(std::vector<fish>& fishes, std::vector<predator>& p);
