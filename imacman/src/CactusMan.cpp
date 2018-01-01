//
// Created by Amel on 29/12/2017.
//

#include "../include/CactusMan.h"
CactusMan::CactusMan(){
    //to change with intial positions:
    pos_x= 0;
    pos_y=0;
    pos_z=0;
}

void CactusMan::moveFront(float step){
    pos_z+=step;
}

void CactusMan::moveLeft(){
    rot_y=-90;
}