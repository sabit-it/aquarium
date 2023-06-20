#pragma once

#include "predator.h"
#include "plankton.h"
#include "../../constants/defines.h"
#include "../../domain/actionc.h"
#include "plankton.h"
#include <chrono>
#include <random>
#include <vector>
#include <string>

struct predator;

struct plankton;

struct fish {

    explicit fish(int cur_x = -1, int cur_y = -1) {
        if(cur_x == -1 && cur_y == -1){
            life_start = std::chrono::steady_clock::now();
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(100, 1720);
            std::uniform_int_distribution<> life(-20000, 20000);
            fish_additional_life = life(gen);
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

    plankton* prey = nullptr;

    bool hunt = false;
    bool found_close_prey = false;

    COORD eye_cord;
    COORD inner_eye;

    int path_count = 0;

    float hungry_level = 40;
    int age = 0;
    float x, y;

    long long fish_additional_life;
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
    bool is_hunted = false;

    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> start_run;
    std::chrono::time_point<std::chrono::steady_clock> life_start;

    bool found_close_predator = false;
    bool find_predator(std::vector<predator>& predators);

    void move(std::vector<predator>& predators, std::vector<plankton>& planktons);

    void set_rotation();

    void run_set_rotation();

    bool find_plankton(std::vector<plankton>& planktons);

};

void move_fishes(std::vector<fish>& fishes, std::vector<predator>& p, std::vector<plankton>& planktons);
