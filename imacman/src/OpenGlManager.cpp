//
// Created by natshez on 30/12/2017.
//

#include "OpenGlManager.hpp"

/**
 * OpenGlManager()
 * initialise scene lights and glew
 */
OpenGlManager::OpenGlManager() : lightLeft(glm::vec3(1.2),"global_left"), lightRight(glm::vec3(1.2),"global_right"), playerLight(glm::vec3(1),"player"), models() {}
int OpenGlManager::init(const char* argv0){

    appFolderPath = Tools::getFolderPath(argv0);
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

}
/**
 * draw all RenderModels
 * @param windowManager
 * @param viewMatrix
 * @param playerPosition
 */
void OpenGlManager::drawAll(glimac::SDLWindowManager &windowManager, glm::mat4 &viewMatrix, glm::vec2 playerPosition){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.7, 0.3, 0.2, 1);

    //transformation
    lightRight.setDirection( glm::vec4(5,3,-25,0));
    lightRight.setDirection(viewMatrix * lightRight.getDirection());

    lightLeft.setDirection(glm::vec4(10,20,20,0));

    playerLight.setDirection(glm::vec4(playerPosition.x,1,1,1));
    playerLight.transform(glm::vec3(0),windowManager.getTime(),glm::vec3(0,0,1),glm::vec3(1));
    playerLight.setDirection(viewMatrix * playerLight.getDirection());

    for (int it = 0; it < models.size() ; ++it) {
        models[it]->render(viewMatrix,lightRight,playerLight,lightLeft);
    }

    // Update the display
    windowManager.swapBuffers();
}
/**
 * draw a Menu (a cube with a texture near the camera)
 * @param windowManager
 * @param model
 * @param viewMatrix
 */
void OpenGlManager::drawMenu(glimac::SDLWindowManager &windowManager, RenderModel *model, glm::mat4 &viewMatrix){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.7, 0.3, 0.2, 1);

    model->render(viewMatrix,lightRight,playerLight,lightLeft);

    // Update the display
    windowManager.swapBuffers();
}
/**
 * addRenderModel()
 * add a Rendermodel to the RenderModels vector and add his uniforms variables to the GPUProgram
 * @param RenderModel *
 */
void OpenGlManager::addRenderModel(RenderModel *model) {
    model->addProgramUniforms(lightRight,playerLight,lightLeft);
    models.push_back(model);
}
/**
 * Destructor
 */
OpenGlManager::~OpenGlManager(){
    models.erase(models.begin(),models.end());
}
/**
 * getAppFolderPath()
 * App path needed to load assets
 * @return std::string
 */
const std::string &OpenGlManager::getAppFolderPath() const {
    return appFolderPath;
}
/**
 * removeRenderModel()
 * @param RenderModel *
 */
void OpenGlManager::removeRenderModel(RenderModel *model) {
    models.erase(std::find(models.begin(), models.end(), model));
}
/**
 * getConversionFactor()
 * @return
 */
float OpenGlManager::getConversionFactor() const {
    return conversionFactor;
}
