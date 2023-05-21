#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "src/model/entities/fish.h"
#include "src/model/entities/predator.h"
#include "src/view/show_functions.h"
#include "src/model/additionaly_functionality/adding.h"
#include "src/model/additionaly_functionality/path_generate.h"
#include "src/model/additionaly_functionality/deleting.h"
#include "src/model/entities/plankton.h"

int main() {
    std::vector<fish> fishes(10);
    std::vector<predator> predators;
    std::vector<plankton> planktons;
    int count = 0;

    int n = 0;

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Aquarium");
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

    Sprite sprite;
    sf::Image image;
    image.loadFromFile(BACKGROUND_PATH);
    Texture texture;
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    long long eat_time = 0;
    while (window.isOpen()){
        eat_time += 1;
        Event event{};
        while (window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }

        show_background(window, sprite);
        show_fish(fishes, window);
        move_fishes(fishes, predators);
        show_predators(predators, window);
        move_predators(predators, fishes);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        window.display();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 5000 > count) {
            count++;
//            add_fish(temp);
//            add_predator(pr);
        }
    }

    return 0;
}
