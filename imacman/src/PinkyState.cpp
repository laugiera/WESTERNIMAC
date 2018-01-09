//
// Created by Amel on 1/1/2018.
//

#include "PinkyState.hpp"


PinkyState::~PinkyState(){
}

PinkyState::PinkyState() : GhostState(-1, -1) {

}


void PinkyState::setColor(RenderModel *renderModel) {
    renderModel->setModelColor(glm::vec3(0.588, 0.423, 0.250),glm::vec3(1),glm::vec3(1));
}

