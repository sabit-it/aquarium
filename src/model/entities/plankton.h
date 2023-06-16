#pragma once
#include <string>
#include "fish.h"
//#include "../../domain/deleting.h"
#include "../../constants/defines.h"
#include <chrono>
#include <random>

struct plankton {
    plankton(int cur_x = -1, int cur_y = -1){
        if(cur_x == -1 && cur_y == -1){
            std::random_device rd;
            std::mt19937 gen(rd());
            life_start = std::chrono::steady_clock::now();
            std::uniform_int_distribution<> life(-20000, 20000);
            additional_life = life(gen);

            std::uniform_int_distribution<> dis(100, 1720);
            x = dis(gen);

            std::uniform_int_distribution<> dis_y(100, 780);
            y = dis_y(gen);
        }
    }
    float x, y;
    float move_x, move_y;

    long long additional_life;
    int type = 1;

    int path_count;

    int age;

    bool is_alive = true;

    bool destination_right;
    float angle_destination;
    float angle;

    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> life_start;

    void move();

    void set_rotation();
};

void move_planktons(std::vector<plankton>& planktons);