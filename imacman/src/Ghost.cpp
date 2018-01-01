//
// Created by Amel on 1/1/2018.
//

#include "Ghost.hpp"


Ghost::Ghost(Tile *tile) : tile(tile) {}

Ghost::Ghost(){}

Ghost::~Ghost(){}

void Ghost::move(CactusMan &Player){

}

void Ghost::Drop(CactusMan &Player){
    int currentLives =Player.getLives();
    Player.setLives(currentLives-1);

}

