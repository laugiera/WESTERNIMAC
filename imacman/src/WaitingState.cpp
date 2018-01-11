//
// Created by Lou on 09/01/2018.
//

#include "WaitingState.hpp"

WaitingState::WaitingState(int timer) : GhostState(timer, -1) {
}

void WaitingState::move(glm::vec2 &position, Tile *&currentTile) {
    countDown();
}

void WaitingState::setColor(RenderModel *renderModel) {
    renderModel->setModelColor(glm::vec3(0, 0, 0),glm::vec3(1),glm::vec3(1));
}
