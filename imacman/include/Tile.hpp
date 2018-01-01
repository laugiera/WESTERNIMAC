//
// Created by Lou Landry on 29/12/2017.
//

#ifndef IMACMAN_TILE_HPP
#define IMACMAN_TILE_HPP

#include <glm/vec2.hpp>
#include <vector>
#include <iostream>
#include "GameElement.hpp"
#include "CactusMan.hpp"

enum {WALL, EMPTY, GHOST, PACMAN, GUM, SUPERGUM, FRUIT, ELEVATOR};


class Tile {
public:
    Tile() = default;

    Tile(int id, const glm::vec2 &center, const std::vector<Tile *> &neighbours, const int &initiateState);

    friend std::ostream & operator<<(std::ostream & stream, Tile & tile);

    void changeElement(int elementType);

    void render();

    void drop(CactusMan &player);

    int type(); //returns tile type

    int getInitialState() const;

    const glm::vec2 &getCenter() const;

    const std::vector<Tile *> &getNeighbours() const;

private:
    int id;
    glm::vec2 center; // x and y coordinates relative to the gameboard
    std::vector<Tile *> neighbours;
    int initialState;
    GameElement * element;

};


#endif //IMACMAN_TILE_HPP
