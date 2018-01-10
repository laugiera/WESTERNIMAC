//
// Created by Lou Landry on 31/12/2017.
//

#ifndef IMACMAN_GAMEELEMENT_HPP
#define IMACMAN_GAMEELEMENT_HPP

#include <glm/vec2.hpp>
#include "OpenGlManager.hpp"

class RenderModel;

enum {WALL, EMPTY, GHOST, PACMAN, GUM, SUPERGUM, FRUIT, ELEVATOR, PORTAL};

class GameElement {
public:
    GameElement();

    virtual ~GameElement();

    virtual void render(glm::vec2 position) = 0;

    virtual int drop() = 0;

    virtual void createRenderModel() = 0;

protected:
    RenderModel * renderModel;

};


#endif //IMACMAN_GAMEELEMENT_HPP
