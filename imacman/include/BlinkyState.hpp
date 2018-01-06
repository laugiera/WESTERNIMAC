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
    void move(glm::vec2 & position, float &rotation);
    void setColor(RenderModel * renderModel);
    void color();


};


#endif //IMACMAN_BLINKYGHOST_HPP
