//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_BLINKYGHOST_HPP
#define IMACMAN_BLINKYGHOST_HPP

#include "Ghost.hpp"


class BlinkyGhost : public Ghost{

public:

    BlinkyGhost(Tile *tile);

    ~BlinkyGhost();
    void move(CactusMan &Player);
    void color();


};


#endif //IMACMAN_BLINKYGHOST_HPP
