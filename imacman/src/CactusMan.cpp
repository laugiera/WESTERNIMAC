//
// Created by Amel on 29/12/2017.
//

#include <glm/vec2.hpp>
#include "CactusMan.hpp"

CactusMan::CactusMan(Tile *tile) : startingTile (tile), tile(tile) {
    position = glm::vec2(tile->getCenter().x, tile->getCenter().y);
    rotation = 0;
    score=0;
    lives = 3;
    computeDirectionVectors();
    createRenderModel();
}

CactusMan::~CactusMan(){


}

void CactusMan::moveFront(float direction){
    float test = 0.55;
    glm::vec2 previousPosition = position;
    //std::cout<<"vec pos front = " << position <<std::endl;
    //std::cout<<" int vec pos mod  = " << (int)((position.x)*1000) % 500 << " | y= " << (int)((position.y)*1000) % 500<<std::endl;

    if(cam2D){

        rotation = (direction>0)?180: 0;
        computeDirectionVectors();
        position += glm::vec2(frontVector.x, frontVector.z) * test;
        direction = glm::abs(direction); //we don't need the signed direction anymore cause we have backward orientation
        /*Amel
        if(((int)((position.y)*1000) % 500 == 0) || ((int)((position.y)*1000) % 500 == 0 )){
            position += glm::vec2(frontVector.x, frontVector.z) * glm::abs(speed);
        }
        */
    } else {
        position += glm::vec2(frontVector.x, frontVector.z) * test * direction; //direction needs to be signed
    }
    if(!isOnWalkableTile()){
        position = previousPosition;
    } else {
        position = previousPosition + (glm::vec2(frontVector.x, frontVector.z) * speed * direction);
    }
}

void CactusMan::rotateLeft(){
    if(isOnCrossRoad()){
        rotation += 90;
        computeDirectionVectors();
    }
}

void CactusMan::moveLeft(float direction){
    //std::cout<<" int vec pos mod  = " << (int)((position.x)*1000) % 500 << " | y= " << (int)((position.y)*1000) % 500<<std::endl;

    if(cam2D) {
// Lou
        float test = 0.55;
        glm::vec2 previousPosition = position;
        rotation = (direction > 0) ? -90 : 90;
        computeDirectionVectors();
        position += glm::vec2(frontVector.x, frontVector.z) * test;
        if (!isOnWalkableTile()) {
            position = previousPosition;
        } else {
            position = previousPosition + (glm::vec2(frontVector.x, frontVector.z) * speed);
        }

//
/*Amel
        glm::vec2 previousPosition = position;
        rotation = (speed>0)?-90: 90;
        computeDirectionVectors();
        if(((int)((position.y)*1000) % 500 == 0) || ((int)((position.y)*1000) % 500 == 0 )){
                position += glm::vec2(frontVector.x, frontVector.z) * glm::abs(speed);
                std::cout<<"vec pos left = " << position <<std::endl;
            }
            if(!isOnWalkableTile()){
                position = previousPosition;
            }
*/
    } else {
        if(direction>0){
            rotateLeft();
        } else {
            rotateRight();
        }
    }
}

void CactusMan::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cactus", appFolderPath + "/imacman", "3D2", "texture");
        renderModel->setModelColor(glm::vec3(0.850, 0.913, 0.788),glm::vec3(1),glm::vec3(1));
        renderModel->setTexture(appFolderPath + "/textures/cactus.jpg");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

void CactusMan::render() {
    if(cam2D){
        renderModel->transform(glm::vec3(position.x, 0, position.y), rotation, glm::vec3(0,1,0), glm::vec3(1));
    }

}

float CactusMan::getRotation() const {
    return rotation;
}

void CactusMan::computeDirectionVectors() {
    float _rotation = glm::radians(rotation);
    frontVector = glm::vec3(glm::cos(0.f)*glm::sin(_rotation),
                              glm::sin(0.f),
                              glm::cos(0.f)*glm::cos(_rotation));
    leftVector = glm::vec3(glm::sin(_rotation+(glm::pi<float>()*0.5)),
                             0,
                             glm::cos(_rotation+(glm::pi<float>()*0.5)));

}

const glm::vec3 &CactusMan::getFrontVector() const {
    return frontVector;
}

const glm::vec3 &CactusMan::getLeftVector() const {
    return leftVector;
}

void CactusMan::rotateRight() {
    if(isOnCrossRoad()){
        rotation -= 90;
        computeDirectionVectors();
    }
}

bool CactusMan::isOnTile(const Tile *tile) {
        if(position.x >= tile->getCenter().x -0.5 &&
           position.x <= tile->getCenter().x + 0.5&&
           position.y >= tile->getCenter().y - 0.5 &&
           position.y <= tile->getCenter().y + 0.5 ) {
            return true;
        }
    return false;
}

bool CactusMan::isOnCrossRoad() {
    if (tile->getNeighbours().size() == 2 &&
        (*tile->getNeighbours()[0])->isAligned(*tile->getNeighbours()[1])) {
        return false;
    }
    else if (glm::distance(position, tile->getCenter()) > 0.2){
        return false;
    }
    return true;
}

bool CactusMan::isOnWalkableTile() {
    if(isOnTile(tile)){
        return true;
    } else {
        for(int i = 0; i<tile->getNeighbours().size(); i++){
            if(isOnTile(*(tile->getNeighbours().at(i)))){
                Tile ** newTile = tile->getNeighbours().at(i);
                tile = *newTile;
                return true;
            }
        }
        return false;
    }
}

int CactusMan::dropTile() {
    if(glm::distance(position, tile->getCenter()) < 0.2){
        int type = tile->drop();
        switch (type) {
            case GUM :
                score += 10;
                break;
            case SUPERGUM :
                //score += 50;
                break;
            case FRUIT :
                score += 500;
                break;
            default:
                break;
        }
        return type;
    }
    return EMPTY;
}

void CactusMan::testGhostEncounter(std::vector<Ghost *> &ghosts) {
    for(Ghost * ghost : ghosts){
        if (glm::distance(position, ghost->getPosition()) < 0.3) {
            int what = ghost->collide();
            switch (what) {
                case -1:
                    lives --;
                    for(Ghost * ghost : ghosts){
                        ghost->returnToStartPos();
                    }
                    tile = startingTile;
                    position = tile->getCenter();
                    break;
                default:
                    score += what;
                    ghost->returnToStartPos();
                    for(Ghost * ghost : ghosts){
                        ghost->setScaredState();
                    }
                    break;
            }
        }
    }

}

void CactusMan::setCam2D(bool cam2D) {
    CactusMan::cam2D = cam2D;
}


