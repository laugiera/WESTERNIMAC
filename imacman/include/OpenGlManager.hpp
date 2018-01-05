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
#include "Tools.hpp"

class OpenGlManager {
public:
    int init(const char* argv0);
    void drawAll(glimac::SDLWindowManager &windowManager, glm::mat4 &viewMatrix);
    void addRenderModel(RenderModel * model);
    void removeRenderModel(RenderModel * model);

    float getConversionFactor() const;

    OpenGlManager(OpenGlManager const&)= delete; //removed
    void operator=(OpenGlManager const&)= delete; //removed
    static OpenGlManager& getInstance()
    {
        static OpenGlManager    instance;
        // Instantiated on first use.
        return instance;
    }
    const std::string &getAppFolderPath() const;

private :
    float conversionFactor = 15.0;
    Light light;
    std::vector<RenderModel*> models;
    std::string appFolderPath;
    OpenGlManager();
    ~OpenGlManager();


};


#endif //IMACMAN_OPENGLMANAGER_H
