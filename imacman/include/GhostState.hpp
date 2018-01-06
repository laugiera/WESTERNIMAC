//
// Created by Lou Landry on 06/01/2018.
//

#ifndef IMACMAN_GHOSTSTATE_HPP
#define IMACMAN_GHOSTSTATE_HPP

#include "OpenGlManager.hpp"


class GhostState {
public:
    GhostState() = default;
    GhostState(int timer, int collisionReturn);

    virtual ~GhostState();

    virtual void move(glm::vec2 & position, float &rotation) = 0;
    virtual void setColor(RenderModel * renderModel) = 0;
    void countDown();

    int getTimer() const;
    int getCollisionReturn() const;

    void setSpeed(float speed);

private:
    int timer;
    int collisionReturn;
    float speed;

};


#endif //IMACMAN_GHOSTSTATE_HPP
