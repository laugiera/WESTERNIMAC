//
// Created by Lou Landry on 06/01/2018.
//

#ifndef IMACMAN_SCAREDGHOSTSTATE_HPP
#define IMACMAN_SCAREDGHOSTSTATE_HPP

#include "GhostState.hpp"

class ScaredGhostState : public GhostState {
public:
    ScaredGhostState(int timer, int collisionReturn);
    void move(glm::vec2 &position, Tile* & currentTile);
    void setColor(RenderModel * renderModel);

};


#endif //IMACMAN_SCAREDGHOSTSTATE_HPP
