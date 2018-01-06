//
// Created by Amel on 1/1/2018.
//

#include "InkyState.hpp"


InkyState::~InkyState(){}

InkyState::InkyState() : GhostState(-1, -1) {

}
void InkyState::move(glm::vec2 &position, float &rotation) {

}

void InkyState::setColor(RenderModel *renderModel) {
    renderModel->setModelColor(glm::vec3(0.466, 0.478, 0.172),glm::vec3(1),glm::vec3(1));
}

