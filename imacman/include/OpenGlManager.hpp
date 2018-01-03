//
// Created by natshez on 30/12/2017.
//

#ifndef IMACMAN_OPENGLMANAGER_H
#define IMACMAN_OPENGLMANAGER_H

#define GLEW_STATIC
#include <glimac/SDL2WindowManager.hpp>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <memory>
#include <vector>
#include "RenderModel.hpp"
#include "Light.hpp"

class OpenGlManager {
public:
    int init(char* argv0);
    void drawAll(glimac::SDLWindowManager &windowManager, glm::mat4 &viewMatrix);
    void addRenderModel(RenderModel * model);
    OpenGlManager(OpenGlManager const&)= delete; //removed
    void operator=(OpenGlManager const&)= delete; //removed
    static OpenGlManager& getInstance()
    {
        static OpenGlManager    instance;
        // Instantiated on first use.
        return instance;
    }

private :
    Light light;
    std::vector<RenderModel*> models;
    OpenGlManager();
    ~OpenGlManager();

};


#endif //IMACMAN_OPENGLMANAGER_H
