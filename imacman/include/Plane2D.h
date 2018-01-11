//
// Created by natshez on 11/01/2018.
//

#ifndef IMACMAN_PLANE2D_H
#define IMACMAN_PLANE2D_H

#include <iostream>
#include <glm/vec2.hpp>
#include "OpenGlManager.hpp"

class RenderModel;

class Plane2D {
public:
    Plane2D(){};
    void createRenderModel();
    void render();

    RenderModel *getRenderModel() ;

    void setRenderModel(RenderModel *renderModel);

private:
    RenderModel * renderModel;
};


#endif //IMACMAN_PLANE2D_H
