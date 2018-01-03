//
// Created by Amel on 29/12/2017.
//

#ifndef IMACMAN_CACTUSMAN_HPP
#define IMACMAN_CACTUSMAN_HPP
#include<cmath>
#include <glm/vec2.hpp>
#include "Tile.hpp"

class Tile;  //temp
class RenderModel;


class CactusMan {
public:
    CactusMan() = default;
    CactusMan(Tile *tile);

    ~CactusMan();
    void createRenderModel();
    void render();
    void moveFront(float step);
    void moveLeft(float step);
    void rotateLeft();

    //getters setters
    const int &getLives() const {return _lives;}
    void setLives(int lives) {_lives =lives ;}

    const int &getScore() const {return _score;}
    void setScore(int score){_score=score ;}

    const glm::vec2 &getPosition() const {return position;}
    void setPosition(glm::vec2 pos){position=pos ;}

    const glm::vec2 &getRotation() const;

private :
    Tile * tile;
    glm::vec2 position;
    glm::vec2 rotation;
    int _score, _lives;
    RenderModel * renderModel;

};


#endif //IMACMAN_CACTUSMAN_HPP
