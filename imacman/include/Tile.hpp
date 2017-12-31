//
// Created by Lou Landry on 29/12/2017.
//

#ifndef IMACMAN_TILE_HPP
#define IMACMAN_TILE_HPP

#include <glm/vec2.hpp>
#include <vector>
#include <iostream>
#include "GameElement.hpp"

enum {WALL, EMPTY, GHOST, PACMAN, GUM, SUPERGUM, FRUIT};


class Tile {
public:
    Tile() = default;

    Tile(int id, const glm::vec2 &center, const std::vector<Tile *> &neighbours, const int &initiateState);

    friend std::ostream & operator<<(std::ostream & stream, Tile & tile);

private:
    int id;
    glm::vec2 center; // x and y coordinates relative to the gameboard
    std::vector<Tile *> neighbours;
    int initialState;
    GameElement * element;

};


#endif //IMACMAN_TILE_HPP