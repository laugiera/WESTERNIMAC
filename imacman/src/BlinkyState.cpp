//
// Created by Amel on 1/1/2018.
//

#include "BlinkyState.hpp"

BlinkyState::BlinkyState() : GhostState(-1, -1) {}

BlinkyState::~BlinkyState(){
}

void BlinkyState::setColor(RenderModel *renderModel) {
    renderModel->setModelColor(glm::vec3(0.156, 0.235, 0.086),glm::vec3(1),glm::vec3(1));

}

