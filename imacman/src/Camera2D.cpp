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

/**
 * Increase or Decrease distance to camera target
 * @param delta
 */
void Camera2D::zoom(float delta){
    m_fDistance += delta;
}

/**
 * Compute the view matrixfrom the camera orientation and position
 * @return
 */
glm::mat4 Camera2D::getViewMatrix() const{
    glm::mat4 viewMatrix = glm::mat4(1.f);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1,0,0));
    viewMatrix = glm::translate(viewMatrix,glm::vec3(-positionX, -m_fDistance, -positionY));
    return viewMatrix;
}

/**
 * Ajust Camera position and orientation to follow the player
 * @param player
 */
void Camera2D::follow(const CactusMan &player) {
    positionX = player.getPosition().x * (OpenGlManager::getInstance().getConversionFactor());
    positionY = player.getPosition().y ;
    m_fAngleY = player.getRotation();
}
