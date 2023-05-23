#include "plankton.h"

void plankton::set_rotation() {
    angle_destination = asin((move_y / PLANKTON_SPEED) * 180 / M_PI);
    angle = angle_destination;
    destination_right = abs(std::asin(move_y / PLANKTON_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
}


void plankton::move(){
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - life_start).count() > PLANKTON_LIFE_TIME){
        is_alive = false;
        x = -100;
        y = -100;
    } else {
        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(2000, 10000);

        if(current_time > dis(gen)) {
            start = std::chrono::steady_clock::now();

            std::uniform_int_distribution<> dis(-PLANKTON_SPEED, PLANKTON_SPEED);
            move_x = dis(gen);
            move_y = sqrt(PLANKTON_SPEED * PLANKTON_SPEED - move_x * move_x);

            std::uniform_int_distribution<> dis_zn(1, 2);
            int sign = dis_zn(gen);
            if(sign == 2){
                move_y = -move_y;
            }

            destination_right = abs(std::asin(move_y / PLANKTON_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
            angle_destination = asin(move_y / PLANKTON_SPEED) * 180 / M_PI;

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

void move_planktons(std::vector<plankton>& planktons){
    for(auto& p: planktons){
        if(p.is_alive){
            p.move();
        }
    }
}
