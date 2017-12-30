//
// Created by Lou Landry on 29/12/2017.
//

#include "Tile.hpp"

Tile::Tile(int id, const glm::vec2 &center, float size, const std::vector<int> &neighboors) : id(id), center(center),
                                                                                              size(size),
                                                                                              neighboors(neighboors) {}
