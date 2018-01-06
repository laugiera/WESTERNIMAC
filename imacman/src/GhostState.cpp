//
// Created by Lou Landry on 06/01/2018.
//

#include "GhostState.hpp"

GhostState::GhostState(int timer, int collisionReturn) : timer(timer), collisionReturn(collisionReturn), speed(0.2) {}

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

