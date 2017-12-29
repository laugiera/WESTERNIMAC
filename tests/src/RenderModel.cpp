//
// Created by natshez on 29/12/2017.
//

#include "RenderModel.h"

RenderModel::RenderModel(const std::string &_modelPath)
        : model(ObjectModel(_modelPath)),
          vbo(glcustom::VBO()),ibo(glcustom::IBO()),vao(glcustom::VAO())
{
    vbo.fillBuffer(model.getVertices_vector());
    ibo.fillBuffer(model.getIndices_vector());
    vao.fillBuffer(model.getVertices_vector(), &vbo, &ibo);

    setModelMatrix();
}

void RenderModel::addModelUniforms(glcustom::GPUProgram &program){
    std::vector<std::string> uniformVariables;
    uniformVariables.push_back("uMVPMatrix");
    uniformVariables.push_back("uMVMatrix");
    uniformVariables.push_back("uNormalMatrix");

    program.addUniforms(uniformVariables);
}

void RenderModel::setModelMatrix(){
    modelMatrix = glm::mat4(1.0f);
}
void RenderModel::render(const glm::mat4 &viewMatrix, glcustom::GPUProgram &program){
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), Utils::windowWidth/Utils::windowHeight, 0.1f, 100.f);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 modelViewProjMatrix = projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));

    program.sendUniformMat4("uMVPMatrix", modelViewProjMatrix);
    program.sendUniformMat4("uMVMatrix", modelViewMatrix);
    program.sendUniformMat4("uNormalMatrix", normals);

    vao.bind();
    glDrawElements(GL_TRIANGLES, model.getIndices_vector().size(), GL_UNSIGNED_INT, 0);
    vao.debind();

}

void RenderModel::transform(const glm::mat4 &transformation){
    modelMatrix = transformation * modelMatrix;
}
