#pragma once

#define FISH_SPEED 5
#define FISH_RUN_SPEED 10
#define PREDATOR_SPEED 7
#define PREDATOR_HUNT_SPEED 15
#define PLANKTON_SPEED 2
#define FISH_RUN_DISTANCE 150
#define PREDATOR_HUNT_DISTANCE 250
#define WIDTH 1920
#define HEIGHT 1080
#define SPRITES_PATH "/home/sabit/Рабочий стол/C++/aquarium_decompostion/resources/"s

#define FIRST_TYPE_PREDATOR_RIGHT "/home/sabit/Рабочий стол/C++/aquarium_decompostion/resources/first_type_predator_right.png"
#define FIRST_TYPE_PREDATOR_LEFT "/home/sabit/Рабочий стол/C++/aquarium_decompostion/resources/first_type_predator_left.png"
#define BACKGROUND_PATH "/home/sabit/Рабочий стол/C++/aquarium_decompostion/resources/background.png"
#define MIN_FISH_COUNT 16
#define MIN_PREDATOR_COUNT 4
#define MIN_PLANKTON_COUNT 100
#define FISH_LIFE_TIME 80000
#define PREDATOR_LIFE_TIME 100000
#define PLANKTON_LIFE_TIME 40000



#define FIRST_FISH_LEFT_EYE {6, 23}
#define FIRST_FISH_RIGHT_EYE {91, 23}
#define SECOND_FISH_LEFT_EYE {24, 36}
#define SECOND_FISH_RIGHT_EYE {76, 36}
#define PREDATOR_LEFT_EYE {27, 49}
#define PREDATOR_RIGHT_EYE {174, 49}

#define PREDATOR_CENTER {100.5, 40}
#define FIRST_FISH_CENTER {48.5, 26.5}
#define SECOND_FISH_CENTER {50, 41}
#define PLANKTON_CENTER {20, 20}

#define FIRST_FISH_WIDTH 97
#define FIRST_FISH_HEIGHT 53

#define SECOND_FISH_WIDTH 100
#define SECOND_FISH_HEIGHT 82

#define PREDATOR_WIDTH 201
#define PREDATOR_HEIGHT 80



#define ACOSD(x) (acos(x) * 180 / M_PI)

#define DOT_PRODUCT(x, y) (x.i * y.i + x.j * y.j)
#define VECT_DIST(x) (sqrtf(x.i * x.i + x.j * x.j))

#define ANGLE_BY_DOT_PRODUCT(x, y) (ACOSD(DOT_PRODUCT(x, y)/(VECT_DIST(x) * VECT_DIST(y))))
