//
// Created by Lou Landry on 31/12/2017.
//

#include "SuperGum.hpp"


void SuperGum::drop(CactusMan &player){
    int currentScore=player.getScore();
    player.setScore(currentScore+200);
    SuperMoodOn=true;
}