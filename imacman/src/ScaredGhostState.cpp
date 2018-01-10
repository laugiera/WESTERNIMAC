//
// Created by Lou Landry on 06/01/2018.
//

#include "ScaredGhostState.hpp"

ScaredGhostState::ScaredGhostState(int timer, int collisionReturn) : GhostState(timer, collisionReturn) {
    speed = 0.005;
}


void ScaredGhostState::move(glm::vec2 &position, Tile* & currentTile) {
    GhostState::move(position, currentTile);
    countDown();
}

void ScaredGhostState::setColor(RenderModel *renderModel) {
    renderModel->setModelColor(glm::vec3(1, 1, 1),glm::vec3(1),glm::vec3(1));
}
