//
// Created by natshez on 03/01/2018.
//

#include "CameraFPS.hpp"

void CameraFPS::computeDirectionVectors()
{
    m_FrontVector = glm::vec3(glm::cos(m_fTheta)*glm::sin(m_fPhi),
                              glm::sin(m_fTheta),
                              glm::cos(m_fTheta)*glm::cos(m_fPhi));
    m_LeftVector = glm::vec3(glm::sin(m_fPhi+(glm::pi<float>()*0.5)),
                             0,
                             glm::cos(m_fPhi+(glm::pi<float>()*0.5)));
    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

CameraFPS::CameraFPS()
{
    m_Position = glm::vec3(0,0,-5);
    m_fPhi = 0;
    m_fTheta = 0;
    computeDirectionVectors();
}

void CameraFPS::moveLeft(float t)
{
    m_Position += m_LeftVector*t;
}

void CameraFPS::moveFront(float t)
{
    m_Position += m_FrontVector*t;
}

glm::mat4 CameraFPS::getViewMatrix() const
{
    return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}

void CameraFPS::follow(const CactusMan &player) {
    m_Position = glm::vec3(player.getPosition().x, 0.8, player.getPosition().y) * (OpenGlManager::getInstance().getConversionFactor());
    m_fPhi = player.getRotation();
    m_FrontVector = player.getFrontVector();
    m_LeftVector = player.getLeftVector();
    moveFront(10);

}

void CameraFPS::rotateLeft(float t) {
        m_fPhi += glm::radians(t);
        computeDirectionVectors();
}

