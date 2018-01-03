//
// Created by Amel on 29/12/2017.
//

#include <glm/vec2.hpp>
#include "CactusMan.hpp"

CactusMan::CactusMan(Tile *tile) : tile(tile) {
    position = glm::vec2(tile->getCenter().x, tile->getCenter().y);
    rotation= glm::vec2(0, 0);

    _score=0;
    _lives = 3;
    createRenderModel();
}

CactusMan::~CactusMan(){


}

void CactusMan::moveFront(float step){
    position.y-=step;
}

void CactusMan::rotateLeft(){
    rotation.y=-90;
}

void CactusMan::moveLeft(float step){
    position.x-=step;
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
    renderModel->transform(glm::vec3(position.x, 0, position.y), 0, glm::vec3(0,1,0), glm::vec3(0.8, 0.5, 0.8));
}

const glm::vec2 &CactusMan::getRotation() const {
    return rotation;
}
