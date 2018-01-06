//
// Created by Amel on 1/1/2018.
//

#include "ClydeState.hpp"

ClydeState::ClydeState() : GhostState(-1, -1) {
}

ClydeState::~ClydeState(){
}
void ClydeState::move(glm::vec2 & position, float &rotation){

}

void ClydeState::setColor(RenderModel *renderModel) {
    renderModel->setModelColor(glm::vec3(0.255, 0.235, 0.086),glm::vec3(1),glm::vec3(1));
}



