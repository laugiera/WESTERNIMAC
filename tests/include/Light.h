//
// Created by natshez on 29/12/2017.
//

#ifndef IMACMAN_LIGHT_H
#define IMACMAN_LIGHT_H


#include <glm/vector_relational.hpp>
#include <glm/matrix.hpp>
#include <GPUProgram.hpp>

class Light {
public:
    Light(const glm::vec3 &_intensity);
    void transform(const glm::mat4 &transformation);
    void addLightUniforms(glcustom::GPUProgram &program);
    void sendLightUniforms(glcustom::GPUProgram &program);

    void setDirection();

private:
    glm::vec4 direction;
    glm::vec3 intensity;

};


#endif //IMACMAN_LIGHT_H
