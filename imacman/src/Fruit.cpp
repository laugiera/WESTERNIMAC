//
// Created by Lou Landry on 31/12/2017.
//

#include "Fruit.hpp"


void Fruit::drop(CactusMan &player){
    int currentScore=player.getScore();
    player.setScore(currentScore+500);
}