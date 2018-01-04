//
// Created by Amel on 29/12/2017.
//

#include <glm/vec2.hpp>
#include "CactusMan.hpp"

CactusMan::CactusMan(Tile *tile) : tile(tile) {
    position = glm::vec2(tile->getCenter().x, tile->getCenter().y);
    rotation = 0;
    _score=0;
    _lives = 3;
    computeDirectionVectors();
    createRenderModel();
}

CactusMan::~CactusMan(){


}

void CactusMan::moveFront(float step){
    //position.y-=step;
    position += glm::vec2(frontVector.x, frontVector.z) * step;
}

void CactusMan::rotateLeft(){
    rotation += 90;
    computeDirectionVectors();
}

void CactusMan::moveLeft(float step){
    //position.x-=step;
    //position += glm::vec2(leftVector.x, leftVector.z) * step;
    if(step>0){
        rotateLeft();
    } else {
        rotateRight();
    }
}

void CactusMan::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cube", appFolderPath + "/imacman", "3D2", "directionallight");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

void CactusMan::render() {
    renderModel->transform(glm::vec3(position.x, 0, position.y), rotation, glm::vec3(0,1,0), glm::vec3(0.8, 0.5, 0.8));
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
    rotation -= 90;
    computeDirectionVectors();
}
