//
// Created by Lou Landry on 31/12/2017.
//

#include "Portal.hpp"

void Portal::render(glm::vec2 position) {
    renderModel->transform(glm::vec3(position.x, 0, position.y), -90, glm::vec3(0,1,0), glm::vec3(0.1));

}

int Portal::drop() {
    return PORTAL;
}

void Portal::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/portal", appFolderPath + "/imacman", "3D2", "directionallight");
        renderModel->setModelColor(glm::vec3(0.356, 0.509, 0.584),glm::vec3(1),glm::vec3(1));
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}
