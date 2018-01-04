//
// Created by natshez on 30/12/2017.
//

#include "OpenGlManager.hpp"

OpenGlManager::OpenGlManager() : light(glm::vec3(1)), models() {}
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
void OpenGlManager::drawAll(glimac::SDLWindowManager &windowManager, glm::mat4 &viewMatrix){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 1);

    //transformation

    for (int it = 0; it < models.size() ; ++it) {
      //  models[it]->setModelMatrix(glm::translate(glm::mat4(1.0), glm::vec3(1,0,0)));
    }

    light.setDirection();
    light.transform(glm::vec3(0),windowManager.getTime()+100,glm::vec3(0, 1, 0),glm::vec3(1));

    for (int it = 0; it < models.size() ; ++it) {
        models[it]->render(viewMatrix,light);

    }

    // Update the display
    windowManager.swapBuffers();
}

void OpenGlManager::addRenderModel(RenderModel *model) {
    model->addProgramUniforms(light);
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
