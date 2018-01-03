//
// Created by natshez on 03/01/2018.
//

#ifndef IMACMAN_CAMERA2D_H
#define IMACMAN_CAMERA2D_H

#include "Camera.h"

class Camera2D : public Camera{
public:
    Camera2D();
    void moveFront(float delta);
    void moveLeft(float t);
    glm::mat4 getViewMatrix() const;

    private:
        float positionX;
        float m_fDistance;
        float m_fAngleX;
        float m_fAngleY;
};


#endif //IMACMAN_CAMERA2D_H
