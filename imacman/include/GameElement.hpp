//
// Created by Lou Landry on 31/12/2017.
//

#ifndef IMACMAN_GAMEELEMENT_HPP
#define IMACMAN_GAMEELEMENT_HPP

#include <glm/vec2.hpp>
#include "../../tests/include/CactusMan.h"

class GameElement {
public:
    GameElement()= default;

    virtual void render(glm::vec2 position) = 0;

    virtual void drop(CactusMan &player) = 0;

};


#endif //IMACMAN_GAMEELEMENT_HPP
