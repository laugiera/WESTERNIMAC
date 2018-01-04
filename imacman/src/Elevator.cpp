//
// Created by Lou Landry on 31/12/2017.
//

#include "Elevator.hpp"

void Elevator::render(glm::vec2 position) {
    renderModel->transform(glm::vec3(position.x, 0.3 , position.y), 0, glm::vec3(0,1,0), glm::vec3(0.3, 0.3, 0.3));
}

int Elevator::drop() {
    return ELEVATOR;
}

void Elevator::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cube.obj", appFolderPath + "/imacman", "3D2", "directionallight");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}
