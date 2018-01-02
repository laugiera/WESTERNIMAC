//
// Created by natshez on 29/12/2017.
//

#include "RenderModel.h"

RenderModel::RenderModel(const std::string &_modelPath,
                         const glimac::FilePath appPath, const std::string &vertexShader, const std::string &fragmentShader)
        : model(ObjectModel(_modelPath)), program(glcustom::GPUProgram(appPath,vertexShader,fragmentShader))
{
    vbo = glcustom::VBO();
    ibo = glcustom::IBO();
    vao = glcustom::VAO();
    vbo.fillBuffer(model.getVertices_vector());
    ibo.fillBuffer(model.getIndices_vector());
    vao.fillBuffer(model.getVertices_vector(), &vbo, &ibo);

    setModelMatrix();
    program.use();
}

void RenderModel::addProgramUniforms(Light &light){
    std::vector<std::string> uniformVariables;
    uniformVariables.push_back("uMVPMatrix");
    uniformVariables.push_back("uMVMatrix");
    uniformVariables.push_back("uNormalMatrix");
    uniformVariables.push_back("uKd");
    uniformVariables.push_back("uKs");
    uniformVariables.push_back("uShininess");
    uniformVariables.push_back("color");

    program.addUniforms(uniformVariables);
    light.addLightUniforms(program);
}

void RenderModel::setModelMatrix(const glm::mat4 _modelMatrix){
    modelMatrix = _modelMatrix;
}
void RenderModel::render(const glm::mat4 &viewMatrix, Light &light){
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), Utils::windowWidth/Utils::windowHeight, 0.1f, 100.f);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 modelViewProjMatrix = projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));

    program.sendUniformMat4("uMVPMatrix", modelViewProjMatrix);
    program.sendUniformMat4("uMVMatrix", modelViewMatrix);
    program.sendUniformMat4("uNormalMatrix", normals);

//    program.sendUniform1f("uShininess", model.getShininess());
//    program.sendUniformVec3("uKd",model.getKd());
//    program.sendUniformVec3("uKs",model.getKs());
    program.sendUniform1f("uShininess", 64);
    program.sendUniformVec3("uKd",glm::vec3(1));
    program.sendUniformVec3("uKs",glm::vec3(1));
    program.sendUniformVec3("color", model.getColor());
    light.sendLightUniforms(program);

    vao.bind();
    glDrawElements(GL_TRIANGLES, model.getIndices_vector().size(), GL_UNSIGNED_INT, 0);
    vao.debind();

}

void RenderModel::transform(const glm::vec3 &translation, const float angle, const glm::vec3 &axesRotation, const glm::vec3 &scale){
    glm::mat4 transformation = glm::mat4(1.f);
    transformation = glm::scale(transformation,scale);
    transformation = glm::rotate(transformation,angle,axesRotation);
    transformation = glm::translate(transformation, translation);
    modelMatrix = transformation * modelMatrix;
}
