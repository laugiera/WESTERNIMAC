//
// Created by natshez on 11/01/2018.
//

#include "Plane2D.h"
/**
 * Creates the rendermodel for CactusMan
 */
void Plane2D::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cubeMenu", appFolderPath + "/imacman", "3D2", "2D");
        renderModel->setModelColor(glm::vec3(0.8,0.3,0.3),glm::vec3(1),glm::vec3(1));
        renderModel->setTexture(appFolderPath + "/textures/cactus.png");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Updates the RenderModel with the player's coordinates, rotation and scale
 */
void Plane2D::render() {
    renderModel->transform(glm::vec3(0), 0, glm::vec3(1,0,0), glm::vec3(1));
}

RenderModel *Plane2D::getRenderModel()  {
    return renderModel;
}

void Plane2D::setRenderModel(RenderModel *renderModel) {
    Plane2D::renderModel = renderModel;
}
