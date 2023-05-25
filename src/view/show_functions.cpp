#include "../model/entities/fish.h"
#include "../model/entities/predator.h"
#include "../domain/path_generate.h"
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
    Sprite fish_sprite;
    Texture fish_texture;

    for(auto& f: fishes) {
        if(!f.is_alive){
            continue;
        }

        fish_texture.loadFromFile(generate_fish_path(f.type, f.destination_right));

        if(f.type == 1){
            fish_sprite.setTextureRect(sf::IntRect(0, 0, 97, 53));
        } else if(f.type == 2){
            fish_sprite.setTextureRect(sf::IntRect(0, 0, 100, 82));
        }

        fish_sprite.setTexture(fish_texture);

        auto origin = get_origin(f.type);
        fish_sprite.setOrigin(origin.first, origin.second);

        fish_sprite.setPosition(f.x, f.y);

        if(!f.destination_right){
            fish_sprite.setRotation(-f.angle);
        } else {
            fish_sprite.setRotation(f.angle);
        }

        window.draw(fish_sprite);
    }

}

void show_planktons(std::vector<plankton>& planktons, RenderWindow& window){
    Sprite plankton_sprite;
    Texture plankton_texture;
    for(auto& p: planktons){
        if(!p.is_alive){
            continue;
        }

        plankton_texture.loadFromFile(SPRITES_PATH + "plankton.png");

        plankton_sprite.setTexture(plankton_texture);

        plankton_sprite.setOrigin(PLANKTON_CENTER);

        plankton_sprite.setPosition(p.x, p.y);

        window.draw(plankton_sprite);
    }

}


































