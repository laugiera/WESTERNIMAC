//
// Created by natshez on 03/01/2018.
//

#include "Camera2D.h"

Camera2D::Camera2D(){
    m_fDistance = 100;
    m_fAngleX = 90;
    m_fAngleY = 0;
    positionX = 0;
}
void Camera2D::moveFront(float delta){
    m_fDistance += delta;
}
void Camera2D::moveLeft(float t){
    positionX += t;
}

glm::mat4 Camera2D::getViewMatrix() const{
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f),glm::vec3(positionX, 0, -m_fDistance));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0,1,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1,0,0));
    return viewMatrix;
}
