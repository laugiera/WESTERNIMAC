//
// Created by Lou Landry on 06/01/2018.
//

#include "GhostState.hpp"

GhostState::GhostState(int timer, int collisionReturn) : timer(timer), collisionReturn(collisionReturn), speed(0.05) {}

int GhostState::getTimer() const {
    return timer;
}

int GhostState::getCollisionReturn() const {
    return collisionReturn;
}

void GhostState::countDown() {
    timer --;
}

void GhostState::setSpeed(float speed) {
    GhostState::speed = speed;
}

GhostState::~GhostState() {

}

void GhostState::move(glm::vec2 &position, Tile* & currentTile) {
    //default random movement
    int randMax = currentTile->getNeighbours().size();
    srand(time(NULL));
    Tile * nextTile = *(currentTile->getNeighbours()[rand()%randMax]);
    position += (nextTile->getCenter() - position) * speed;
    if(isOnTile(position, nextTile)){
        currentTile = nextTile;
    }

}

bool GhostState::isOnTile(glm::vec2 &position, const Tile *tile) {
    if(position.x >= tile->getCenter().x -0.5 &&
       position.x <= tile->getCenter().x + 0.5&&
       position.y >= tile->getCenter().y - 0.5 &&
       position.y <= tile->getCenter().y + 0.5 ) {
        return true;
    }
    return false;
}

