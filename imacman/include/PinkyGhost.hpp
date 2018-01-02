//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_PINKYGHOST_HPP
#define IMACMAN_PINKYGHOST_HPP
#include "Ghost.hpp"


class PinkyGhost : public Ghost{
public:
    PinkyGhost();

    PinkyGhost(Tile *tile);

    ~PinkyGhost();
    void move(CactusMan &Player);
};


#endif //IMACMAN_PINKYGHOST_HPP
