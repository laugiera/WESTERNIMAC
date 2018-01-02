//
// Created by natshez on 29/12/2017.
//

#ifndef IMACMAN_RENDERMODEL_H
#define IMACMAN_RENDERMODEL_H

#define GLEW_STATIC

#include "ObjectModel.hpp"
#include <VAO.hpp>
#include <GPUProgram.hpp>
#include "Utils.hpp"
#include "Light.hpp"

class RenderModel {
public :
    RenderModel(const std::string &_modelPath,
                const glimac::FilePath appPath, const std::string &vertexShader, const std::string &fragmentShader);
    void addProgramUniforms( Light &light);
    void transform(const glm::vec3 &translation, const float angle, const glm::vec3 &axesRotation, const glm::vec3 &scale);
    void render(const glm::mat4 &viewMatrix, Light &light);
    void setModelMatrix(const glm::mat4 _modelMatrix = glm::mat4(1.f));


private:
    ObjectModel model;
    glcustom::VBO vbo;
    glcustom::VAO vao;
    glcustom::IBO ibo;
    glm::mat4 modelMatrix;
    glcustom::GPUProgram program;
};


#endif //IMACMAN_RENDERMODEL_H
