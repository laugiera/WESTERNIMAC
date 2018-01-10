//
// Created by natshez on 29/12/2017.
//

#include "Light.hpp"

Light::Light(const glm::vec3 &_intensity) : intensity(_intensity)
{
    setDirection();
}

void Light::setDirection() {
    direction = glm::vec4(1,1,10,0);
}

void Light::transform(const glm::vec3 &translation, const float angle, const glm::vec3 &axesRotation, const glm::vec3 &scale){
    glm::mat4 transformation = glm::mat4(1.f);
    transformation = glm::scale(transformation,scale);
    transformation = glm::rotate(transformation,angle,axesRotation);
    transformation = glm::translate(transformation, translation);
    direction = transformation * direction;
}

void Light::addLightUniforms(glcustom::GPUProgram &program){
    std::vector<std::string> uniformVariables;
    uniformVariables.push_back("uLightDir_vs");
    uniformVariables.push_back("uLightIntensity");

    program.addUniforms(uniformVariables);
}

void Light::sendLightUniforms(glcustom::GPUProgram &program){

    program.sendUniformVec4("uLightDir_vs",direction);
    program.sendUniformVec3("uLightIntensity",intensity);

}