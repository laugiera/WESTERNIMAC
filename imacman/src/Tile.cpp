//
// Created by Lou Landry on 29/12/2017.
//

#include "Tile.hpp"

Tile::Tile(int id, const glm::vec2 &center, const std::vector<Tile *> &neighbours, const int &initiateState)
        : id(id), center(center),
          neighbours(neighbours), initialState(initiateState) {}

std::ostream &operator<<(std::ostream &stream, Tile &tile) {
    std::string symbol;
    if(tile.initialState == WALL){
        symbol = "=";
    } else if (tile.initialState == GUM){
        symbol = ".";
    } else if (tile.initialState == SUPERGUM){
        symbol = "*";
    }
    stream << symbol;
    return stream;
}
