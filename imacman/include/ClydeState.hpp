//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_CLYDEGHOST_HPP
#define IMACMAN_CLYDEGHOST_HPP

#include "GhostState.hpp"


class ClydeState : public GhostState{

public:
    ClydeState();
    ~ClydeState();
    void setColor(RenderModel * renderModel);

};


#endif //IMACMAN_CLYDEGHOST_HPP
