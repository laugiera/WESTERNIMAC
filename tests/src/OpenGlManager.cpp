//
// Created by natshez on 30/12/2017.
//

#include "OpenGlManager.h"

OpenGlManager::OpenGlManager(std::vector<RenderModel*> _models):light(glm::vec3(1))
{
models = _models;
}
int OpenGlManager::init(char* argv0){

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    /***** VARIABLES *****/
    Light light = Light(glm::vec3(1));
    for (int it = 0; it <= models.size() ; ++it) {
        models[it]->addProgramUniforms(light);
    }

}
void OpenGlManager::drawAll(glimac::SDLWindowManager &windowManager, glm::mat4 &viewMatrix){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 1);

    //transformation
    for (int it = 0; it <= models.size() ; ++it) {
        models[it]->setModelMatrix();
    }

    light.setDirection();
    light.transform(glm::vec3(0),windowManager.getTime()+100,glm::vec3(0, 1, 0),glm::vec3(1));

    for (int it = 0; it <= models.size() ; ++it) {
        models[it]->transform(glm::vec3(0),windowManager.getTime(),glm::vec3(0, 1, 0),glm::vec3(1));
        models[it]->render(viewMatrix,light);

    }

    // Update the display
    windowManager.swapBuffers();
}
