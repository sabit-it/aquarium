#pragma once
#include "../constants/defines.h"
#include "../model/entities/predator.h"
#include "../model/entities/fish.h"
#include "../model/entities/plankton.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void show_background(RenderWindow& window, Sprite& sprite);

void show_predators(std::vector<predator>& predators, RenderWindow& window);

void show_fish(std::vector<fish>& fishes, RenderWindow& window);

void show_planktons(std::vector<plankton>& planktons, RenderWindow& window);