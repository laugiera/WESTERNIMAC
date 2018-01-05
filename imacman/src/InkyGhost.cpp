//
// Created by Amel on 1/1/2018.
//

#include "InkyGhost.hpp"


InkyGhost::~InkyGhost(){


}
void InkyGhost::move(CactusMan &Player){


}

void InkyGhost::color(){
    renderModel->setModelColor(glm::vec3(0.466, 0.478, 0.172),glm::vec3(1),glm::vec3(1));
}

InkyGhost::InkyGhost(Tile *tile) : Ghost(tile) {
    this->color();
}
