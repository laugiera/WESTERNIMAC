//
// Created by Lou Landry on 06/01/2018.
//

#ifndef IMACMAN_GHOSTSTATE_HPP
#define IMACMAN_GHOSTSTATE_HPP

#include "OpenGlManager.hpp"
#include "Tile.hpp"


class GhostState {
public:
    GhostState() = default;
    GhostState(int timer, int collisionReturn);

    virtual ~GhostState();

    virtual void move(glm::vec2 &position, Tile* & currentTile);
    virtual void setColor(RenderModel * renderModel) = 0;
    void countDown();
    bool isOnTile(glm::vec2 &position, const Tile *tile);

    int getTimer() const;
    int getCollisionReturn() const;

    void setSpeed(float speed);

private:
    int timer;
    int collisionReturn;
protected:
    float speed;

};


#endif //IMACMAN_GHOSTSTATE_HPP
