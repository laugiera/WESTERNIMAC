//
// Created by Amel on 1/1/2018.
//

#include "PinkyGhost.hpp"


PinkyGhost::~PinkyGhost(){


}
void PinkyGhost::move(CactusMan &Player){


}

void PinkyGhost::color(){
    renderModel->setModelColor(glm::vec3(0.588, 0.423, 0.250),glm::vec3(1),glm::vec3(1));
}

PinkyGhost::PinkyGhost(Tile *tile) : Ghost(tile) {
    this->color();
}
