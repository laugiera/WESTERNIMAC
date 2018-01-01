//
// Created by Amel on 29/12/2017.
//

#include "CactusMan.hpp"
CactusMan::CactusMan(){
    //to change with intial positions:
    pos_x= 0;
    pos_y=0;
    pos_z=0;
    score=0;
    lives = 5;
    canMove=true;
}

void CactusMan::moveFront(float step){
    pos_z+=step;
}

void CactusMan::moveLeft(){
    rot_y=-90;
}

void CactusMan::collision(){

    /* solution 1 : make one collision function here and call in the main while loop,
     * takes the data matrix from boardloader and check if it's wall, droppable, ghost ...
     * solution 2 : make collision function in all items the cactus interacts with
     * but i think solution 1 is better that way we call only one function to check collision ...
     * also the data matrix needs to be updated for ghosts and cactus positions...
     * basically the only 2 elements moving in the board ...
     */
}