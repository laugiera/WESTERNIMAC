//
// Created by Lou Landry on 31/12/2017.
//

#include "Portal.hpp"

void Portal::render(glm::vec2 position) {
    renderModel->transform(glm::vec3(position.x, 0.3 , position.y), 0, glm::vec3(0,1,0), glm::vec3(0.3, 0.3, 0.3));
}

int Portal::drop() {
    return PORTAL;
}

void Portal::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cube.obj", appFolderPath + "/imacman", "3D2", "directionallight");
        renderModel->setModelColor(glm::vec3(1,1,0),glm::vec3(0.3412,0.8824,0.7765),glm::vec3(0.3500,0.3500,0.3500));
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}
