#pragma once
#include "../model/entities/fish.h"
#include "../model/entities/predator.h"
#include "../model/entities/plankton.h"
#include "../constants/defines.h"
#include <vector>

void add_fish(std::vector<fish>& fishes);

void add_predator(std::vector<predator>& predators);

void add_plankton(std::vector<plankton>& planktons);