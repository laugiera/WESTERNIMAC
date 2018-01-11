//
// Created by Lou on 09/01/2018.
//

#ifndef IMACMAN_WAITINGSTATE_H
#define IMACMAN_WAITINGSTATE_H

#include "GhostState.hpp"

class WaitingState : public GhostState {
public:
    WaitingState(int timer);
    ~WaitingState() = default;
    void move(glm::vec2 &position, Tile* & currentTile);
    void setColor(RenderModel * renderModel);
};


#endif //IMACMAN_WAITINGSTATE_H
