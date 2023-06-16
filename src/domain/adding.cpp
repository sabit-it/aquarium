#include "adding.h"

void add_fish(std::vector<fish>& fishes){
    if(fishes.size() >= MIN_FISH_COUNT) {
        return;
    }
    float x, y;
    for(auto& fish: fishes){
        if(fish.hungry_level > 50){
            x = fish.x;
            y = fish.y;
        }
    }
    fishes.push_back(fish());
    fishes[fishes.size() - 1].x = x;
    fishes[fishes.size() - 1].y = y;
}

void add_predator(std::vector<predator>& predators){
    if(predators.size() >= MIN_PREDATOR_COUNT) {
        return;
    }
    float x, y;
    for(auto& predator: predators){
        if(predator.hungry_level > 50){
            x = predator.x;
            y = predator.y;
        }
    }
    predators.push_back(predator());
    predators[predators.size() - 1].x = x;
    predators[predators.size() - 1].y = y;
}

void add_plankton(std::vector<plankton>& planktons){
    if(planktons.size() >= MIN_PLANKTON_COUNT){
        return;
    }
    planktons.push_back(plankton());
    planktons[planktons.size() - 1].x = planktons[0].x;
    planktons[planktons.size() - 1].y = planktons[0].y;
}