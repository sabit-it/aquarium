#pragma once

#include "../constants/defines.h"
#include <string>
#include <algorithm>
using namespace std::literals::string_literals;

std::string generate_fish_path(int& n, bool destination){
    if(destination){
        return  SPRITES_PATH + "fish_right_type_"s + std::to_string(n) + ".png";
    }
    return SPRITES_PATH + "fish_left_type_"s + std::to_string(n) + ".png";
}

std::pair<int, int> get_origin(int type){
    if(type == 1){
        return {48, 26};
    }
    return {50, 41};
}

std::string generate_plankton_path(int& n, bool destination){
    if(destination){
        return SPRITES_PATH + "plankton_right_type_"s + std::to_string(n) + ".png"s;
    }
    return SPRITES_PATH + "plankton_left_type_"s + std::to_string(n) + ".png"s;
}