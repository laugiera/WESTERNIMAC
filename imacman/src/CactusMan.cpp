//
// Created by Amel on 29/12/2017.
//

#include <glm/vec2.hpp>
#include "CactusMan.hpp"
CactusMan::CactusMan(){
    //to change with intial positions:
    position= glm::vec2(0,0);
    rotation= glm::vec2(0,0);

    _score=0;
    _lives = 5;
}

CactusMan::~CactusMan(){


}

void CactusMan::moveFront(float step){
    position.y+=step;
}

void CactusMan::moveLeft(){
    rotation.y=-90;
}

CactusMan::CactusMan(Tile *tile) : tile(tile) {
    position= glm::vec2(tile->getCenter().x,tile->getCenter().y);
    rotation= glm::vec2(0,0);

    _score=0;
    _lives = 5;
}
