//
// Created by natshez on 29/12/2017.
//

#ifndef IMACMAN_RENDERMODEL_H
#define IMACMAN_RENDERMODEL_H

#define GLEW_STATIC

#include "ObjectModel.hpp"
#include <VAO.hpp>
#include <GPUProgram.hpp>
#include "Utils.h"

class RenderModel {
public :
    RenderModel(const std::string &_modelPath);
    void addModelUniforms(glcustom::GPUProgram &program);
    void transform(const glm::mat4 &transformation);
    void render(const glm::mat4 &viewMatrix, glcustom::GPUProgram &program);
    void setModelMatrix();

private:
    ObjectModel model;
    glcustom::VBO vbo;
    glcustom::VAO vao;
    glcustom::IBO ibo;
    glm::mat4 modelMatrix;
};


#endif //IMACMAN_RENDERMODEL_H
