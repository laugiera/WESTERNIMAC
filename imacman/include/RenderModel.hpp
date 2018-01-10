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
#include <Texture.hpp>

class RenderModel {
public :
    RenderModel() = default;
    RenderModel(const std::string &_modelPath,
                const glimac::FilePath appPath, const std::string &vertexShader, const std::string &fragmentShader);
    void setModelColor(glm::vec3 _color, glm::vec3 _kd, glm::vec3 _ks);
    void setTexture(const std::string filePath);
    void addProgramUniforms(Light &light,Light &playerLight);
    void transform(const glm::vec3 &translate, const float angle, const glm::vec3 &axesRotation,
                       const glm::vec3 &scale);
    void render(const glm::mat4 &viewMatrix, Light &light,Light &playerLight);
    void setModelMatrix(const glm::mat4 _modelMatrix = glm::mat4(1.f));


private:
    ObjectModel model;
    glcustom::VBO vbo;
    glcustom::VAO vao;
    glcustom::IBO ibo;
    glm::mat4 modelMatrix;
    glcustom::GPUProgram program;
    glcustom::Texture * texture;
};


#endif //IMACMAN_RENDERMODEL_H
