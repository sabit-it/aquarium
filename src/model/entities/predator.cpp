#include "predator.h"
#include "fish.h"
#include "../../constants/defines.h"

void predator::set_rotation() {
    angle_destination = asin(move_y / PREDATOR_SPEED) * 180 / M_PI;
    angle = angle_destination;
    destination_right = abs(std::asin(move_y / PREDATOR_SPEED) * 180 / M_PI) < 90 && move_x >= 0;

}

void move_predators(std::vector<predator>& predators, std::vector<fish>& fishes){
    for(auto& pr: predators){
        if(pr.is_alive) {
            pr.move(fishes);
        }
        if(!pr.is_alive){
            std::cout << "\nno";
        }
    }
}

void predator::move(std::vector<fish> &fishes) {
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - life_start).count() > PREDATOR_LIFE_TIME || hungry_level <= 0){
        is_alive = false;
        x = -100;
        y = -100;
    }

    hungry_level -= 0.05;

    if(hungry_level >= 30){
        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(6000, 12000);

        if(current_time > dis(gen)){

            start = std::chrono::steady_clock::now();
            std::uniform_int_distribution<> dis(-PREDATOR_SPEED, PREDATOR_SPEED);
            move_x = dis(gen);
            move_y = sqrt(PREDATOR_SPEED * PREDATOR_SPEED - move_x * move_x);

            std::uniform_int_distribution<> dis_zn(1, 2);
            int sign = dis_zn(gen);
            if(sign == 2){
                move_y = -move_y;
            }

            destination_right = abs(std::asin(move_y / PREDATOR_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
            angle_destination = asin(move_y / PREDATOR_SPEED) * 180 / M_PI;

        } else {

            x += move_x;
            y += move_y;
            if(x < 100 && move_x < 0){
                move_x = -move_x;
            }
            if(x > WIDTH - 200 && move_x > 0){
                move_x = -move_x;
            }
            if(y < 100 && move_y < 0){
                move_y = -move_y;
            }
            if(y > HEIGHT - 200 && move_y > 0){
                move_y = -move_y;
            }

        }

    } else {

    }

    set_rotation();
}

bool predator::find_fish(std::vector<fish> &fishes) {
    return false;
}

