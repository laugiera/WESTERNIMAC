//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_CLYDEGHOST_HPP
#define IMACMAN_CLYDEGHOST_HPP

#include "Ghost.hpp"


class ClydeGhost : public Ghost{

public:
    ClydeGhost();
    ~ClydeGhost();
    void move(CactusMan &Player);

};


#endif //IMACMAN_CLYDEGHOST_HPP
