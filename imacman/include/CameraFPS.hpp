//
// Created by natshez on 03/01/2018.
//

#ifndef IMACMAN_CAMERAFPS_H
#define IMACMAN_CAMERAFPS_H

#include "Camera.hpp"

class CameraFPS : public  Camera{
public:
    CameraFPS();
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float t);
    void follow(const CactusMan &player);

    glm::mat4 getViewMatrix() const;
private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

    void computeDirectionVectors();
};


#endif //IMACMAN_CAMERAFPS_H
