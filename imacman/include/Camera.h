//
// Created by natshez on 03/01/2018.
//

#ifndef IMACMAN_CAMERA_H
#define IMACMAN_CAMERA_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(){};
    virtual void moveFront(float delta) = 0;
    virtual void moveLeft(float t) = 0;
    virtual glm::mat4 getViewMatrix() const = 0;

};


#endif //IMACMAN_CAMERA_H
