//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_BLINKYGHOST_HPP
#define IMACMAN_BLINKYGHOST_HPP

#include "GhostState.hpp"


class BlinkyState : public GhostState{

public:

    BlinkyState();
    ~BlinkyState();
    void setColor(RenderModel * renderModel);


};


#endif //IMACMAN_BLINKYGHOST_HPP
