//
// Created by natshez on 29/12/2017.
//

#include <OpenGlManager.hpp>
#include "RenderModel.hpp"

/**
 * Constructor
 * Initialise GPUProgram with shaders paths
 * Initialise ObjectModel with model path
 * Fill buffers
 * set the model matrix
 * @param _modelPath
 * @param appPath
 * @param vertexShader
 * @param fragmentShader
 */
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
/**
 * setModelColor()
 * @param _color
 * @param _kd
 * @param _ks
 */
void RenderModel::setModelColor(glm::vec3 _color, glm::vec3 _kd, glm::vec3 _ks){
    model.setColor(_color,_kd,_ks);
}
/**
 * setTexture()
 * @param filePath
 */
void RenderModel::setTexture(const std::string filePath){
     texture = new glcustom::Texture(filePath);
}
/**
 * addProgramUniforms
 * add uniforms variables to the GPUProgram
 * add lights uniforms to the GPUProgram
 * @param globalRight
 * @param playerLight
 * @param globalLeft
 */
void RenderModel::addProgramUniforms( Light &globalRight, Light &playerLight, Light &globalLeft){
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
    globalLeft.addLightUniforms(program);
    globalRight.addLightUniforms(program);
    playerLight.addLightUniforms(program);
}
/**
 * setModelMatrix
 * @param _modelMatrix
 */
void RenderModel::setModelMatrix(const glm::mat4 _modelMatrix){
    modelMatrix = _modelMatrix;
}
/**
 * Render
 * Render a ObjectModel with lights and viewMatrix
 * @param viewMatrix
 * @param globalRight
 * @param playerLight
 * @param globalLeft
 */
void RenderModel::render(const glm::mat4 &viewMatrix, Light &globalRight, Light &playerLight, Light &globalLeft){
    program.use();

    glm::mat4 projMatrix = glm::perspective(glm::radians(85.f), Utils::windowWidth/Utils::windowHeight, 0.1f, 500.f);
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
    globalLeft.sendLightUniforms(program);
    globalRight.sendLightUniforms(program);
    playerLight.sendLightUniforms(program);

    vao.bind();
    glDrawElements(GL_TRIANGLES, model.getIndices_vector().size(), GL_UNSIGNED_INT, 0);
    vao.debind();

    if(texture)
        texture->debind();

}
/**
 * transform()
 * apply a transformation to the modelMatrix
 * @param translate
 * @param angle
 * @param axesRotation
 * @param scale
 */
void RenderModel::transform(const glm::vec3 &translate, const float angle, const glm::vec3 &axesRotation,
                            const glm::vec3 &scale) {
    glm::mat4 transformation = glm::mat4(1.f);
    float conversionFactor = OpenGlManager::getInstance().getConversionFactor();
    transformation = glm::translate(transformation, translate *conversionFactor);
    transformation = glm::rotate(transformation,glm::radians(angle),axesRotation);
    transformation = glm::scale(transformation,scale);
    modelMatrix = transformation/* * modelMatrix*/;
}
