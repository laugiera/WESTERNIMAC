//
// Created by Lou Landry on 31/12/2017.
//

#include "Gum.hpp"


void Gum::drop(CactusMan &player){
    int currentScore=player.getScore();
    player.setScore(currentScore+10);
}