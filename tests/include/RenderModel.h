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
#include "Light.h"

class RenderModel {
public :
    RenderModel(const std::string &_modelPath,
                const glimac::FilePath appPath, const std::string &vertexShader, const std::string &fragmentShader);
    void addProgramUniforms( Light &light);
    void transform(const glm::mat4 &transformation);
    void render(const glm::mat4 &viewMatrix, Light &light);
    void setModelMatrix();


private:
    ObjectModel model;
    glcustom::VBO vbo;
    glcustom::VAO vao;
    glcustom::IBO ibo;
    glm::mat4 modelMatrix;
    glcustom::GPUProgram program;
};


#endif //IMACMAN_RENDERMODEL_H
