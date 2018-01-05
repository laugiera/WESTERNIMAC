//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_INKYGHOST_HPP
#define IMACMAN_INKYGHOST_HPP
#include "Ghost.hpp"


class InkyGhost : public Ghost{

public:
    InkyGhost(Tile *tile);

    ~InkyGhost();
    void move(CactusMan &Player);
    void color();

};


#endif //IMACMAN_INKYGHOST_HPP
