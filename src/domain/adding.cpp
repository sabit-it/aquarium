#include "adding.h"

void add_fish(std::vector<fish>& fishes){
    if(MAX_FISH_COUNT > fishes.size()){
        fishes.push_back(fish());
        fishes[fishes.size() - 1].x = 1800;
        fishes[fishes.size() - 1].y = 100;
    }
}

void add_predator(std::vector<predator>& predators){
    if(MAX_PREDATOR_COUNT > predators.size()){
        predators.push_back(predator());
        predators[predators.size() - 1].x = 200;
        predators[predators.size() - 1].y = 800;
    }
}