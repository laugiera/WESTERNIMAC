//
// Created by natshez on 11/01/2018.
//

#include "CubeMenu.hpp"
/**
 * Creates the rendermodel for CactusMan
 */
void CubeMenu::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cubeMenu", appFolderPath + "/imacman", "3D2", "texture");
        renderModel->setModelColor(glm::vec3(0.5,0.5,0.5),glm::vec3(1),glm::vec3(1));
        renderModel->setTexture(appFolderPath + "/images/menu/MMI.png");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Updates the RenderModel with the player's coordinates, rotation and scale
 */
void CubeMenu::render() {
        renderModel->transform(glm::vec3(0), 0, glm::vec3(1,0,0), glm::vec3(3.65));

}

RenderModel *CubeMenu::getRenderModel()  {
    return renderModel;
}
