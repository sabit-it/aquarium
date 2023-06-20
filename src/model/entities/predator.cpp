#include "predator.h"
#include "fish.h"
#include "../../constants/defines.h"

void predator::set_rotation() {
    angle_destination = asin(move_y / speed) * 180 / M_PI;
    angle = angle_destination;
    destination_right = abs(std::asin(move_y / speed) * 180 / M_PI) < 90 && move_x >= 0;

}

void move_predators(std::vector<predator>& predators, std::vector<fish>& fishes){
    for(auto& pr: predators){
        if(pr.is_alive) {
            pr.move(fishes);
        }
    }
}

void predator::move(std::vector<fish> &fishes) {

    {
        COORD eye;
        COORD inner;
        if (destination_right) {
            inner = PREDATOR_RIGHT_EYE;
        } else {
            inner = PREDATOR_LEFT_EYE;
        }
        inner_eye = inner;
        eye_cord = eye;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> life(-30000, 30000);

    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - life_start).count() > PREDATOR_LIFE_TIME + life(gen) || hungry_level <= 0){
        is_alive = false;
        x = -100;
        y = -100;
    }


    hungry_level -= 0.05;
    if(hunt && !found_close_prey){
        hunt = true;
        found_close_prey = find_fish(fishes);
        speed = PREDATOR_HUNT_SPEED;
    }
    if(hungry_level < 30 && !hunt){
        hunt = true;
        found_close_prey = find_fish(fishes);
        speed = PREDATOR_HUNT_SPEED;
    }
    if(hungry_level >= 90){
        speed = PREDATOR_SPEED;
        hunt = false;
        prey = nullptr;
    }

    if((hungry_level >= 30 && !hunt) || (hunt && !found_close_prey)){
        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(6000, 12000);

        if(current_time > dis(gen)){

            start = std::chrono::steady_clock::now();
            std::uniform_int_distribution<> dis(-speed, speed);
            move_x = dis(gen);
            move_y = sqrt(speed * speed - move_x * move_x);

            std::uniform_int_distribution<> dis_zn(1, 2);
            int sign = dis_zn(gen);
            if(sign == 2){
                move_y = -move_y;
            }

            destination_right = abs(std::asin(move_y / speed) * 180 / M_PI) < 90 && move_x >= 0;
            angle_destination = asin(move_y / speed) * 180 / M_PI;

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

        eye_cord = getFishEyeCoord({x, y}, inner_eye, angle, PREDATOR_WIDTH, PREDATOR_HEIGHT);
        COORD closest_point = {prey->x, prey->y};

        if(findDistanceTwoPoints(closest_point, eye_cord) < 25){
            prey->is_alive = false;
            hungry_level += 30;
            if(hungry_level > 100){
                hungry_level = 100;
            }
            found_close_prey = false;
            prey = nullptr;
        };

        float angle_from_prey = angle_between_two_coordinates(closest_point, eye_cord);
        move_x = cos(angle_from_prey * M_PI / 180) * speed;
        move_y = sin(angle_from_prey * M_PI / 180) * speed;
        x += move_x;
        y += move_y;
    }
    set_rotation();
}

bool predator::find_fish(std::vector<fish> &fishes) {
    bool is_prey_found = false;
    eye_cord = getFishEyeCoord({x, y}, inner_eye, angle, PREDATOR_WIDTH, PREDATOR_HEIGHT);
    float closest_prey = 1e9;
    found_close_prey = false;

    for(int i = 0; i < fishes.size(); i++){
        COORD temp = getClosestFromPoint({fishes[i].x, fishes[i].y}, fishes[i].width, fishes[i].height, fishes[i].angle, eye_cord);
        float temp_distance = findDistanceTwoPoints(temp, eye_cord);
        if(temp_distance < closest_prey && temp_distance <= PREDATOR_HUNT_DISTANCE && !fishes[i].is_hunted){
            is_prey_found = true;
            prey = &fishes[i];
            fishes[i].is_hunted = true;
        }
    }

    return is_prey_found;
}
