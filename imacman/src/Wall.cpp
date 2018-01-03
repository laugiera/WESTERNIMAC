//
// Created by Lou Landry on 31/12/2017.
//

#include "Wall.hpp"

void Wall::render(glm::vec2 position) {
    renderModel->transform(glm::vec3(position.x, 0, position.y), 0, glm::vec3(0,1,0), glm::vec3(1, 1, 1));
}

void Wall::drop(CactusMan &player) {

}

void Wall::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cube", appFolderPath + "/imacman", "3D2", "directionallight");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}
