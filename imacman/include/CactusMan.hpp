//
// Created by Amel on 29/12/2017.
//

#ifndef IMACMAN_CACTUSMAN_HPP
#define IMACMAN_CACTUSMAN_HPP
#include<cmath>
#include <glm/vec3.hpp>

class CactusMan {

public:
    CactusMan();
    ~CactusMan();
    void moveFront(float step);
    void moveLeft();

    const int &getLives() {return _lives;}
    void setLives(int lives) {_lives =lives ;}

    const int &getScore() {return _score;}
    void setScore(int score){_score=score ;}

    const glm::vec2 &getPosition() {return position;}
    void setPosition(glm::vec2 pos){position=pos ;}

private :
    glm::vec2 position;
    glm::vec2 rotation;
    int _score, _lives;

};


#endif //IMACMAN_CACTUSMAN_HPP
