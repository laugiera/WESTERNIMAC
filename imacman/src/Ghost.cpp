//
// Created by Amel on 1/1/2018.
//

#include "Ghost.hpp"


Ghost::Ghost(Tile *tile) : tile(tile) {
    position = tile->getCenter();
    createRenderModel();
}

Ghost::Ghost(){}

Ghost::~Ghost(){}

void Ghost::move(CactusMan &Player){

}

void Ghost::Drop(CactusMan &Player){
    int currentLives =Player.getLives();
    Player.setLives(currentLives-1);

}

void Ghost::render() {
    renderModel->transform(glm::vec3(position.x, 0, position.y), 0, glm::vec3(0,1,0), glm::vec3(0.5, 0.7, 0.5));
}

void Ghost::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cube", appFolderPath + "/imacman", "3D2", "directionallight");
        renderModel->setModelColor(glm::vec3(0,0,1),glm::vec3(0.3412,0.8824,0.7765),glm::vec3(0.3500,0.3500,0.3500));
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}



