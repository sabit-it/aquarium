#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "src/model/entities/predator.h"
#include "src/view/show_functions.h"
#include "src/domain/adding.h"
#include "src/model/entities/plankton.h"
#include "src/domain/deleting.h"
int main() {
    std::vector<fish> fishes(10);
    std::vector<predator> predators;
    std::vector<plankton> planktons(80);
    int count = 0;

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Aquarium");
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

    Sprite sprite;
    sf::Image image;
    image.loadFromFile(BACKGROUND_PATH);
    Texture texture;
    texture.loadFromImage(image);
    sprite.setTexture(texture);


    while (window.isOpen()){
        Event event{};
        while (window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }

        show_background(window, sprite);
        show_fish(fishes, window);
        move_fishes(fishes, predators, planktons);
        show_predators(predators, window);
        move_predators(predators, fishes);
        show_planktons(planktons, window);
        move_planktons(planktons);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        window.display();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 5000 > count) {
            count++;
            add_fish(fishes);
            add_predator(predators);
        }
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000 > count) {
            add_plankton(planktons);
        }
        delete_fishes(fishes);
        delete_planktons(planktons);
        delete_predator(predators);
    }

    return 0;
}
