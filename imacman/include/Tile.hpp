//
// Created by Lou Landry on 29/12/2017.
//

#ifndef IMACMAN_TILE_HPP
#define IMACMAN_TILE_HPP

#include <glm/vec2.hpp>
#include <vector>



class Tile {
public:
    Tile() = default;

    Tile(int id, const glm::vec2 &center, float size, const std::vector<int> &neighboors);

private:
    int id;
    glm::vec2 center; // x and y coordinates relative to the gameboard
    float size;
    std::vector<int> neighboors;

};


#endif //IMACMAN_TILE_HPP
