#include "fish.h"
#include "predator.h"
#include "../../constants/defines.h"
#include "../../domain/geometry.h"
#include "../../domain/actionc.h"
#include <random>
#include <chrono>
#include <type_traits>

bool fish::find_predator(std::vector<predator> &predators) {
    bool is_predator_found = false;
    eye_cord = getFishEyeCoord({x, y}, inner_eye, angle, width, height);
    float closest_predator = 1e9;
    found_close_predator = false;

    for(int i = 0; i < predators.size(); i++) {
        COORD temp = getClosestFromPoint({predators[i].x, predators[i].y}, PREDATOR_WIDTH, PREDATOR_HEIGHT, predators[i].angle, eye_cord);
        float temp_distance = findDistanceTwoPoints(temp, eye_cord);
        if(temp_distance < closest_predator && temp_distance <= FISH_RUN_DISTANCE){
            is_predator_found = true;
            predator_x = temp.x;
            predator_y = temp.y;
        } else if(temp_distance < closest_predator && temp_distance <= 200){
            distance_predator = temp_distance;
            closest_predator_x = temp.x;
            closest_predator_y = temp.y;
            found_close_predator = true;
        }

    }

    return is_predator_found;
}

void fish::set_rotation() {
    angle_destination = asin(move_y / FISH_SPEED) * 180 / M_PI;
    angle = angle_destination;
    destination_right = abs(std::asin(move_y / FISH_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
}

void fish::run_set_rotation() {
    angle_destination = asin(move_y / FISH_RUN_SPEED) * 180 / M_PI;
    angle = angle_destination;
    destination_right = abs(std::asin(move_y / FISH_RUN_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
}

void fish::move(std::vector<predator>& predators, std::vector<plankton>& planktons){

    {
        COORD eye;
        COORD inner;
        if (type == 1) {
            if (destination_right) {
                inner = FIRST_FISH_RIGHT_EYE;
            } else {
                inner = FIRST_FISH_LEFT_EYE;
            }
        } else {
            if (destination_right) {
                inner = SECOND_FISH_RIGHT_EYE;
            } else {
                inner = SECOND_FISH_LEFT_EYE;
            }
        }
        inner_eye = inner;
        eye_cord = eye;
    }

    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - life_start).count() > FISH_LIFE_TIME + fish_additional_life || hungry_level <= 0){
        is_alive = false;
        x = -100;
        y = -100;
    }
    hungry_level -= 0.05;

    if(find_predator(predators)){
        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_run).count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1000, 1000);
        if(current_time > dis(gen) && is_first) {
            predator_found = true;
            float delta_x = eye_cord.x - predator_x;
            float delta_y = eye_cord.y - predator_y;

            COORD dest;
            float angle_from_predator;

            angle_from_predator = (float) (asin(delta_y / findDistanceTwoPoints(eye_cord, {predator_x, predator_y})) *
                                           180 / M_PI);

            if (delta_x < 0) {
                dest.x = -(float) cos(angle_from_predator * M_PI / 180) * FISH_RUN_SPEED;
            } else {
                dest.x = (float) cos(angle_from_predator * M_PI / 180) * FISH_RUN_SPEED;
            }

            dest.y = (float) sin(angle_from_predator * M_PI / 180) * FISH_RUN_SPEED;
            move_x = dest.x;
            move_y = dest.y;
            destination_right = abs(std::asin(move_y / FISH_RUN_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
            angle_destination = asin(move_y / FISH_RUN_SPEED) * 180 / M_PI;

//            run_set_rotation();
            is_first = false;

        } else {
            if (x < 50 && move_x < 0) {
                if(move_y >= 0){
                    move_x = 0;
                    move_y = FISH_RUN_SPEED;
                } else {
                    move_x = 0;
                    move_y = -FISH_RUN_SPEED;
                }
            }
            if (x > WIDTH - 200 && move_x > 0) {
                if(move_y >= 0){
                    move_x = 0;
                    move_y = FISH_RUN_SPEED;
                } else {
                    move_x = 0;
                    move_y = -FISH_RUN_SPEED;
                }            }
            if (y < 50 && move_y < 0) {
                if(move_x >= 0){
                    move_x = FISH_RUN_SPEED;
                    move_y = 0;
                } else {
                    move_x = -FISH_RUN_SPEED;
                    move_y = 0;
                }
            }
            if (y > HEIGHT - 200 && move_y > 0) {
                if(move_x >= 0){
                    move_x = FISH_RUN_SPEED;
                    move_y = 0;
                } else {
                    move_x = -FISH_RUN_SPEED;
                    move_y = 0;
                }
            }
            x += move_x;
            y += move_y;
            run_set_rotation();
        }

    } else {
        hungry_level -= 0.05;

        found_close_prey = find_plankton(planktons);
        if(hungry_level <= 70 && found_close_prey){
            prey->is_alive = false;
            hungry_level += 25;
            found_close_prey = false;
            prey = nullptr;
        }

        is_first = true;
        bool go_ = false;
        if(predator_found){
            predator_found = false;
            go_ = true;
        }
        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::uniform_int_distribution<> dis(2000, 10000);
        std::random_device rd;
        std::mt19937 gen(rd());
        if(current_time > dis(gen) || go_) {

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

            while (true){
                if(found_close_predator && distance(eye_cord.x + move_x, eye_cord.y + move_y, closest_predator_x, closest_predator_x) <
                        distance(eye_cord.x, eye_cord.y, closest_predator_x, closest_predator_x)){
                    std::uniform_int_distribution<> dis(-FISH_SPEED, FISH_SPEED);
                    move_x = dis(gen);
                    move_y = sqrt(FISH_SPEED * FISH_SPEED - move_x * move_x);

                    std::uniform_int_distribution<> dis_zn(1, 2);
                    int sign = dis_zn(gen);
                    if(sign == 2){
                        move_y = -move_y;
                    }
                } else {
                    start = std::chrono::steady_clock::now();
                    break;
                }
            }

            destination_right = abs(std::asin(move_y / FISH_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
            angle_destination = asin(move_y / FISH_SPEED) * 180 / M_PI;
            set_rotation();

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
        set_rotation();
    }
}

void move_fishes(std::vector<fish>& fishes, std::vector<predator>& predators, std::vector<plankton>& planktons){
    for(auto& f: fishes){
        if(f.is_alive){
            f.move(predators, planktons);
        }
    }
}

bool fish::find_plankton(std::vector<plankton>& planktons){
    bool is_prey_found = false;
    eye_cord = getFishEyeCoord({x, y}, inner_eye, angle, width, height);
    float closest_prey = 1e9;
    found_close_prey = false;

    for(int i = 0; i < planktons.size(); i++){
        COORD temp = {planktons[i].x, planktons[i].y};
        float temp_distance = findDistanceTwoPoints(temp, eye_cord);
        if(temp_distance < closest_prey && temp_distance <= 20){
            is_prey_found = true;
            prey = &planktons[i];
        }
    }

    return is_prey_found;
}