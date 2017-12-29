//
// Created by natshez on 29/12/2017.
//

#include "Light.h"

Light::Light(const glm::vec3 &_ks, const glm::vec3 &_kd,
             const glm::vec3 &_intensity) : ks(_ks), kd(_kd),intensity(_intensity)
{
    shininess = 64;
    setDirection();
}

void Light::setDirection() {
    direction = glm::vec4(1,1,0,0);
}

void Light::transform(const glm::mat4 &transformation){
    direction = transformation * direction;
}

void Light::addLightUniforms(glcustom::GPUProgram &program){
    std::vector<std::string> uniformVariables;
    uniformVariables.push_back("uKd");
    uniformVariables.push_back("uKs");
    uniformVariables.push_back("uShininess");
    uniformVariables.push_back("uLightDir_vs");
    uniformVariables.push_back("uLightIntensity");

    program.addUniforms(uniformVariables);
}

void Light::sendLightUniforms(glcustom::GPUProgram &program){
    program.sendUniform1f("uShininess", shininess);
    program.sendUniformVec4("uLightDir_vs",direction);
    program.sendUniformVec3("uKd",kd);
    program.sendUniformVec3("uKs",ks);
    program.sendUniformVec3("uLightIntensity",intensity);

}