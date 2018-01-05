//
// Created by Amel on 1/1/2018.
//

#include "BlinkyGhost.hpp"


BlinkyGhost::~BlinkyGhost(){


}
void BlinkyGhost::move(CactusMan &Player){


}

void BlinkyGhost::color(){
    renderModel->setModelColor(glm::vec3(0.156, 0.235, 0.086),glm::vec3(1),glm::vec3(1));
}

BlinkyGhost::BlinkyGhost(Tile *tile) : Ghost(tile) {
    this->color();
}
