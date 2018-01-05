//
// Created by Amel on 1/1/2018.
//

#include "ClydeGhost.hpp"


ClydeGhost::~ClydeGhost(){


}
void ClydeGhost::move(CactusMan &Player){


}

void ClydeGhost::color(){
    renderModel->setModelColor(glm::vec3(1, 0.960, 0.341),glm::vec3(1),glm::vec3(1));
}

ClydeGhost::ClydeGhost(Tile *tile) : Ghost(tile) {
    this->color();
}
