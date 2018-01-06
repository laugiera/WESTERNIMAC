//
// Created by Lou Landry on 06/01/2018.
//

#include "ScaredGhostState.hpp"

ScaredGhostState::ScaredGhostState(int timer, int collisionReturn) : GhostState(timer, collisionReturn) {
    setSpeed(0.03);
}

void ScaredGhostState::move(glm::vec2 &position, float &rotation) {
    countDown();
}

void ScaredGhostState::setColor(RenderModel *renderModel) {
    renderModel->setModelColor(glm::vec3(1, 1, 1),glm::vec3(1),glm::vec3(1));

}
