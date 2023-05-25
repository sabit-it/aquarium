cmake_minimum_required(VERSION 3.25)
project(aquarium_decomosition)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(aquarium_decompostion src/model/entities/predator.cpp src/model/entities/fish.cpp main.cpp src/view/show_functions.cpp src/domain/adding.cpp src/model/entities/plankton.cpp src/domain/actions.c)

target_link_libraries(aquarium_decompostion sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
