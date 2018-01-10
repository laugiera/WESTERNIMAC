//
// Created by natshez on 03/01/2018.
//

#ifndef IMACMAN_CAMERA_H
#define IMACMAN_CAMERA_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CactusMan.hpp"
#include "OpenGlManager.hpp"

class Camera {
public:
    Camera(){};
    virtual glm::mat4 getViewMatrix() const = 0;
    virtual void follow(const CactusMan & player) = 0;

};


#endif //IMACMAN_CAMERA_H
