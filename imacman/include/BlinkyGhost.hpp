//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_BLINKYGHOST_HPP
#define IMACMAN_BLINKYGHOST_HPP

#include "Ghost.hpp"


class BlinkyGhost : public Ghost{

public:
    BlinkyGhost();
    ~BlinkyGhost();
    void move(CactusMan &Player);


};


#endif //IMACMAN_BLINKYGHOST_HPP