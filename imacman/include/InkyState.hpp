//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_INKYGHOST_HPP
#define IMACMAN_INKYGHOST_HPP
#include "GhostState.hpp"


class InkyState : public GhostState{

public:
    InkyState();
    ~InkyState();
    void setColor(RenderModel * renderModel);

};


#endif //IMACMAN_INKYGHOST_HPP
