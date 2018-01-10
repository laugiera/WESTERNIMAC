//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_PINKYGHOST_HPP
#define IMACMAN_PINKYGHOST_HPP
#include "GhostState.hpp"


class PinkyState : public GhostState{
public:
    PinkyState();
    ~PinkyState();
    void setColor(RenderModel * renderModel);
};


#endif //IMACMAN_PINKYGHOST_HPP
