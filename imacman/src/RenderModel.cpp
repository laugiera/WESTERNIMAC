//
// Created by natshez on 29/12/2017.
//

#include <OpenGlManager.hpp>
#include "RenderModel.hpp"

RenderModel::RenderModel(const std::string &_modelPath,
                         const glimac::FilePath appPath, const std::string &vertexShader, const std::string &fragmentShader)
        : model(ObjectModel(_modelPath)), vbo(), ibo(), vao(), program(glcustom::GPUProgram(appPath,vertexShader,fragmentShader))
{

    texture = nullptr;
    vbo.fillBuffer(model.getVertices_vector());
    ibo.fillBuffer(model.getIndices_vector());
    vao.fillBuffer(model.getVertices_vector(), &vbo, &ibo);

    setModelMatrix();
}

void RenderModel::setModelColor(glm::vec3 _color, glm::vec3 _kd, glm::vec3 _ks){
    model.setColor(_color,_kd,_ks);
}

void RenderModel::setTexture(const std::string filePath){
     texture = new glcustom::Texture(filePath);
}

void RenderModel::addProgramUniforms(Light &light,Light &playerLight){
    std::vector<std::string> uniformVariables;
    uniformVariables.push_back("uMVPMatrix");
    uniformVariables.push_back("uMVMatrix");
    uniformVariables.push_back("uNormalMatrix");
    uniformVariables.push_back("uKd");
    uniformVariables.push_back("uKs");
    uniformVariables.push_back("uShininess");
    uniformVariables.push_back("color");
    if(texture)
        uniformVariables.push_back("uTexture");

    program.addUniforms(uniformVariables);
    light.addLightUniforms(program);
    playerLight.addLightUniforms(program);
}

void RenderModel::setModelMatrix(const glm::mat4 _modelMatrix){
    modelMatrix = _modelMatrix;
}
void RenderModel::render(const glm::mat4 &viewMatrix, Light &globalLight, Light &playerLight){
    program.use();

    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), Utils::windowWidth/Utils::windowHeight, 0.1f, 500.f);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 modelViewProjMatrix = projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));

    program.sendUniformMat4("uMVPMatrix", modelViewProjMatrix);
    program.sendUniformMat4("uMVMatrix", modelViewMatrix);
    program.sendUniformMat4("uNormalMatrix", normals);

    if(texture){
        texture->bind(texture->getM_id());
        program.sendUniformTextureUnit("uTexture", 0);
    }

    program.sendUniformVec3("uKd",model.getKd());
    program.sendUniformVec3("uKs",model.getKs());
    program.sendUniform1f("uShininess", 64);
    program.sendUniformVec3("color", model.getColor());
    globalLight.sendLightUniforms(program);
    playerLight.sendLightUniforms(program);

    vao.bind();
    glDrawElements(GL_TRIANGLES, model.getIndices_vector().size(), GL_UNSIGNED_INT, 0);
    vao.debind();

    if(texture)
        texture->debind();

}


void RenderModel::transform(const glm::vec3 &translate, const float angle, const glm::vec3 &axesRotation,
                            const glm::vec3 &scale) {
    glm::mat4 transformation = glm::mat4(1.f);
    float conversionFactor = OpenGlManager::getInstance().getConversionFactor();
    transformation = glm::translate(transformation, translate *conversionFactor);
    transformation = glm::rotate(transformation,glm::radians(angle),axesRotation);
    transformation = glm::scale(transformation,scale);
    modelMatrix = transformation/* * modelMatrix*/;
}
