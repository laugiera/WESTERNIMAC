//
// Created by Amel on 1/1/2018.
//

#include "Ghost.hpp"

Ghost::Ghost(){


}
Ghost::~Ghost(){


}

void Ghost::Drop(CactusMan &Player){
    int currentLives =Player.getLives();
    Player.setLives(currentLives-1);

}