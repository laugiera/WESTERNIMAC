//
// Created by natshez on 30/12/2017.
//

#include "OpenGlManager.hpp"

OpenGlManager::OpenGlManager() : light(glm::vec3(1.5),"global"), playerLight(glm::vec3(2),"player"), models() {}
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
void OpenGlManager::drawAll(glimac::SDLWindowManager &windowManager, glm::mat4 &viewMatrix, glm::vec2 playerPosition){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.7, 0.3, 0.2, 1);

    //transformation
    light.setDirection(viewMatrix * glm::vec4(1,1,1,0));
    light.transform(glm::vec3(0),windowManager.getTime(),glm::vec3(0,0,1),glm::vec3(1));
    playerLight.setDirection(viewMatrix * glm::vec4(1,1,1,1));
    playerLight.transform(glm::vec3(0),windowManager.getTime(),glm::vec3(0,0,1),glm::vec3(1));

    for (int it = 0; it < models.size() ; ++it) {
        models[it]->render(viewMatrix,light,playerLight);
    }

    // Update the display
    windowManager.swapBuffers();
}
void OpenGlManager::drawMenu(glimac::SDLWindowManager &windowManager, RenderModel *model, glm::mat4 &viewMatrix){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.7, 0.3, 0.2, 1);

    //transformation
    light.setDirection(viewMatrix * glm::vec4(1,1,1,0));
    light.transform(glm::vec3(0),windowManager.getTime(),glm::vec3(0,0,1),glm::vec3(1));
    playerLight.setDirection(viewMatrix * glm::vec4(1,1,1,1));
    playerLight.transform(glm::vec3(0),windowManager.getTime(),glm::vec3(0,0,1),glm::vec3(1));

    model->render(viewMatrix,light,playerLight);

    // Update the display
    windowManager.swapBuffers();
}

void OpenGlManager::addRenderModel(RenderModel *model) {
    model->addProgramUniforms(light,playerLight);
    models.push_back(model);
}

OpenGlManager::~OpenGlManager(){
    models.erase(models.begin(),models.end());
}

const std::string &OpenGlManager::getAppFolderPath() const {
    return appFolderPath;
}

void OpenGlManager::removeRenderModel(RenderModel *model) {
    models.erase(std::find(models.begin(), models.end(), model));
}

float OpenGlManager::getConversionFactor() const {
    return conversionFactor;
}
