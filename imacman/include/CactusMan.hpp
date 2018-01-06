//
// Created by Amel on 29/12/2017.
//

#ifndef IMACMAN_CACTUSMAN_HPP
#define IMACMAN_CACTUSMAN_HPP
#include<cmath>
#include <glm/vec2.hpp>
#include "Tile.hpp"
#include "Ghost.hpp"

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
    void rotateRight();
    void computeDirectionVectors();
    bool isOnTile(const Tile * tile);
    bool isOnCrossRoad();
    bool isOnWalkableTile();
    int dropTile();
    void testGhostEncounter(std::vector<Ghost*> & ghosts);

    void setCam2D(bool cam2D);

    //getters setters
    const int &getLives() const {return lives;}
    void setLives(int _lives) {lives =_lives ;}

    const int &getScore() const {return score;}
    void setScore(int _score){score= _score ;}

    const glm::vec2 &getPosition() const {return position;}
    void setPosition(glm::vec2 pos){position=pos ;}

    float getRotation() const;

    const glm::vec3 &getFrontVector() const;

    const glm::vec3 &getLeftVector() const;

private :
    Tile * startingTile;
    Tile * tile;
    glm::vec2 position;
    float rotation;
    glm::vec3 frontVector;
    glm::vec3 leftVector;
    int score, lives;
    RenderModel * renderModel;
    bool cam2D = false;

};


#endif //IMACMAN_CACTUSMAN_HPP
