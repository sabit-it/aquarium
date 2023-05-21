#include "../model/entities/fish.h"
#include "../model/entities/predator.h"
#include "show_functions.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void show_background(RenderWindow& window, Sprite& sprite){
    window.draw(sprite);
}


void show_predators(std::vector<predator>& predators, RenderWindow& window){
    sf::Image predator_image;
    Texture predator_texture;
    Sprite predator_sprite;

    for(auto& p: predators){
        if(!p.is_alive){
            continue;
        }
        if(p.destination_right){
            predator_image.loadFromFile(FIRST_TYPE_PREDATOR_RIGHT);
        } else {
            predator_image.loadFromFile(FIRST_TYPE_PREDATOR_LEFT);
        }
        predator_texture.loadFromImage(predator_image);
        predator_sprite.setTexture(predator_texture);

        predator_sprite.setOrigin(100, 50);
        predator_sprite.setPosition(p.x, p.y);

        if(!p.destination_right){
            predator_sprite.setRotation(-p.angle);
        } else {
            predator_sprite.setRotation(p.angle);
        }

        window.draw(predator_sprite);
    }

}


void show_fish(std::vector<fish>& fishes, RenderWindow& window){
    sf::Image fish_image;
    Texture fish_texture;
    Sprite fish_sprite;

    for(auto& f: fishes) {
        if(!f.is_alive){
            continue;
        }
        if(f.destination_right){
            fish_image.loadFromFile(FIRST_TYPE_RIGHT_PATH);
        } else {
            fish_image.loadFromFile(FIRST_TYPE_LEFT_PATH);
        }
        fish_texture.loadFromImage(fish_image);
        fish_sprite.setTexture(fish_texture);

        fish_sprite.setOrigin(50, 25);
        fish_sprite.setPosition(f.x, f.y);

        if(!f.destination_right){
            fish_sprite.setRotation(-f.angle);
        } else {
            fish_sprite.setRotation(f.angle);
        }

        window.draw(fish_sprite);
    }

}
