//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_GHOST_HPP
#define IMACMAN_GHOST_HPP
#include "CactusMan.hpp"


class Ghost {

public:
    Ghost();
    virtual ~Ghost();
    virtual void move(CactusMan &Player);
    void Drop(CactusMan &Player);
};


#endif //IMACMAN_GHOST_HPP
