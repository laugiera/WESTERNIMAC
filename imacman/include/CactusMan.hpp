//
// Created by Amel on 29/12/2017.
//

#ifndef IMACMAN_CACTUSMAN_HPP
#define IMACMAN_CACTUSMAN_HPP
#include<cmath>
#include <glm/vec3.hpp>
#include "Tile.hpp"

class CactusMan {

public:
    CactusMan();

    CactusMan(Tile *tile);

    ~CactusMan();
    void moveFront(float step);
    void moveLeft(float step);
    void rotateLeft();
    const int &getLives() {return _lives;}
    void setLives(int lives) {_lives =lives ;}

    const int &getScore() {return _score;}
    void setScore(int score){_score=score ;}

    const glm::vec2 &getPosition() {return position;}
    void setPosition(glm::vec2 pos){position=pos ;}

private :
    Tile * tile;
    glm::vec2 position;
    glm::vec2 rotation;
    int _score, _lives;

};


#endif //IMACMAN_CACTUSMAN_HPP
