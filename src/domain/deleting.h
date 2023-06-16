#pragma once

#include "../model/entities/fish.h"
#include "../model/entities/plankton.h"
#include "../model/entities/predator.h"

std::vector<int> get_fishes_to_delete(std::vector<fish>& fishes){
    std::vector<int> fishes_to_delete;
    for(int i = 0; i < fishes.size(); i++){
        if(!fishes[i].is_alive){
            fishes_to_delete.push_back(i);
        }
    }
    return fishes_to_delete;
}

void delete_fishes(std::vector<fish>& fishes){
    int diff = 0;
    for(auto& i: get_fishes_to_delete(fishes)){
        fishes.erase(fishes.begin() + i - diff);
    }
}


std::vector<int> get_predators_to_delete(std::vector<predator>& predators){
    std::vector<int> predators_to_delete;
    for(int i = 0; i < predators.size(); i++){
        if(!predators[i].is_alive){
            predators_to_delete.push_back(i);
        }
    }
    return predators_to_delete;
}

void delete_predator(std::vector<predator>& predators){
    int diff = 0;
    for(auto& i: get_predators_to_delete(predators)){
        predators.erase(predators.begin() + i - diff);
    }
}

std::vector<int> get_planktons_to_delete(std::vector<plankton>& planktons){
    std::vector<int> planktons_to_delete;
    for(int i = 0; i < planktons.size(); i++){
        if(!planktons[i].is_alive){
            planktons_to_delete.push_back(i);
        }
    }
    return planktons_to_delete;
}

void delete_planktons(std::vector<plankton>& planktons){
    int diff = 0;
    for(auto& i: get_planktons_to_delete(planktons)){
        planktons.erase(planktons.begin() + i - diff);
    }
}

