#pragma once

#include "../entities/fish.h"
#include "../entities/plankton.h"
#include "../entities/predator.h"

template<typename T>
std::vector<int> get_dead_animal(std::vector<T>& animals){
    std::vector<int> fishes_to_delete;
    for(int i = 0; i < animals.size(); i++){
        if(!animals[i].is_alive){
            fishes_to_delete.push_back(i);
        }
    }
    return fishes_to_delete;
}

template<typename T>
void delete_animals(std::vector<T>& animals){
    int dif = 0;
    for(auto i: get_dead_animal(animals)){
        animals.erase(animals.begin() + i - dif);
        dif++;
    }
}
