//
// Created by natshez on 11/01/2018.
//

#ifndef IMACMAN_CUBEMENU_H
#define IMACMAN_CUBEMENU_H

#include <iostream>
#include <glm/vec2.hpp>
#include "OpenGlManager.hpp"

class RenderModel;

class CubeMenu {
public:
    CubeMenu(){};
    void createRenderModel();
    void render();

    RenderModel *getRenderModel() ;

    void setRenderModel(RenderModel *renderModel);

private:
    RenderModel * renderModel;


};


#endif //IMACMAN_CUBEMENU_H
