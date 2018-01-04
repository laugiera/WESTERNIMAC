//
// Created by Lou Landry on 29/12/2017.
//

#ifndef IMACMAN_TILE_HPP
#define IMACMAN_TILE_HPP

#include <glm/vec2.hpp>
#include <vector>
#include <iostream>
#include "OpenGlManager.hpp"
#include "Droppable.hpp"

enum {WALL, EMPTY, GHOST, PACMAN, GUM, SUPERGUM, FRUIT, ELEVATOR};

class CactusMan;
class GameElement;

class Tile {
public:
    Tile() = default;

    virtual ~Tile();

    Tile(int id, const glm::vec2 &center, const std::vector<Tile **> &neighbours, const int &initiateState);

    friend std::ostream & operator<<(std::ostream & stream, Tile & tile);

    void changeElement(int elementType);

    void render();

    void drop(CactusMan &player);

    bool isAligned(Tile * tile);

    int type(); //returns tile type

    int getInitialState() const;

    const int &getId() const;

    const glm::vec2 &getCenter() const;

    const std::vector<Tile **> &getNeighbours() const;

    void createRenderModel();

private:
    int id;
    glm::vec2 center; // x and y coordinates relative to the gameboard
    std::vector<Tile **> neighbours;
    int initialState;
    GameElement * element;
    RenderModel * renderModel;

};


#endif //IMACMAN_TILE_HPP
