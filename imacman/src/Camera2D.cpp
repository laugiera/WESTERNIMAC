//
// Created by natshez on 03/01/2018.
//

#include "Camera2D.hpp"

Camera2D::Camera2D(){
    m_fDistance = 100;
    m_fAngleX = 90;
    m_fAngleY = 0;
    positionX = 0;
    positionY = 0;
}

//fcts de déplacement à enlever qd on cleanera
void Camera2D::zoom(float delta){
    m_fDistance += delta;
}
void Camera2D::moveLeft(float t){
    positionX += t;
}

void Camera2D::moveFront(float t){
    positionY += t;
}

glm::mat4 Camera2D::getViewMatrix() const{
    glm::mat4 viewMatrix = glm::mat4(1.f);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1,0,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-m_fAngleY-180), glm::vec3(0,1,0));
    viewMatrix = glm::translate(viewMatrix,glm::vec3(-positionX, -m_fDistance, -positionY));


    return viewMatrix;
}

void Camera2D::follow(CactusMan &player) {
    positionX = player.getPosition().x * (OpenGlManager::getInstance().getConversionFactor());
    positionY = player.getPosition().y * (OpenGlManager::getInstance().getConversionFactor());
    m_fAngleY = player.getRotation();
}
