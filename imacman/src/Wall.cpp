//
// Created by Lou Landry on 31/12/2017.
//

#include "Wall.hpp"

void Wall::render(glm::vec2 position) {
    renderModel->transform(glm::vec3(position.x, 0, position.y), 0, glm::vec3(0,1,0), glm::vec3(1, 0.5, 1));
}

int Wall::drop() {
    return WALL;
}

void Wall::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/wall", appFolderPath + "/imacman", "3D2", "texture");
        renderModel->setModelColor(glm::vec3(0.898, 0.874, 0.823),glm::vec3(0.510, 0.157, 0.157),glm::vec3(1));
        renderModel->setTexture(appFolderPath + "/textures/wood.png");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}
