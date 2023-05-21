#include "fish.h"
#include "predator.h"
#include "../../constants/defines.h"
#include "../../domain/geometry.h"
#include <random>
#include <chrono>


bool fish::find_predator(std::vector<predator> &predators) {
    bool predator_find = distance_predator < 1e8;
    for(int i = 0; i < predators.size(); i++){
        float cur_distance = distance(x, y, predators[i].x, predators[i].y);
        if(cur_distance <= FISH_RUN_DISTANCE && cur_distance < distance_predator){
            if(cur_distance < distance_predator) {
                predator_find = true;
                predator_x = predators[i].x;
                predator_y = predators[i].y;
                distance_predator = cur_distance;
            }
        }
    }
    return predator_find;
}

void fish::set_rotation() {
    angle_destination = asin(move_y / FISH_SPEED) * 180 / M_PI;
    angle = angle_destination;
    destination_right = abs(std::asin(move_y / FISH_SPEED) * 180 / M_PI) < 90 && move_x >= 0;

}

void fish::move(std::vector<predator>& predators){
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - life_start).count() > FISH_LIFE_TIME || hungry_level <= 0){
        is_alive = false;
        x = -100;
        y = -100;
    }
    hungry_level -= 0.05;

    if(find_predator(predators)){


    } else {

        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(2000, 10000);

        if(current_time > dis(gen)) {

            distance_predator = 1e9;

            start = std::chrono::steady_clock::now();

            std::uniform_int_distribution<> dis(-FISH_SPEED, FISH_SPEED);
            move_x = dis(gen);
            move_y = sqrt(FISH_SPEED * FISH_SPEED - move_x * move_x);

            std::uniform_int_distribution<> dis_zn(1, 2);
            int sign = dis_zn(gen);
            if(sign == 2){
                move_y = -move_y;
            }

            destination_right = abs(std::asin(move_y / FISH_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
            angle_destination = asin(move_y / FISH_SPEED) * 180 / M_PI;

        } else {

            x += move_x;
            y += move_y;
            if(x < 50 && move_x < 0){
                move_x = -move_x;
            }
            if(x > WIDTH - 200 && move_x > 0){
                move_x = -move_x;
            }
            if(y < 50 && move_y < 0){
                move_y = -move_y;
            }
            if(y > HEIGHT - 200 && move_y > 0){
                move_y = -move_y;
            }
        }
    }
    set_rotation();
}

void move_fishes(std::vector<fish>& fishes, std::vector<predator>& p){
    for(auto& f: fishes){
        if(f.is_alive){
            f.move(p);
        }
    }
}