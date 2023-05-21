#include "plankton.h"

void plankton::move(std::vector<fish>& fishes){
    if(!find_fish(fishes)){
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - life_start).count() > PLANKTON_LIFE_TIME){
            is_alive = false;
            x = -100;
            y = -100;
        } else {

        }
    } else {

    }

}