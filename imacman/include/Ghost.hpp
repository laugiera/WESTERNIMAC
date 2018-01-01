//
// Created by Lou Landry on 01/01/2018.
//

#ifndef IMACMAN_GHOST_HPP
#define IMACMAN_GHOST_HPP

#include "Tile.hpp"

class Ghost {
public:
    Ghost(Tile *tile);

private:
    Tile * tile;

};


#endif //IMACMAN_GHOST_HPP
