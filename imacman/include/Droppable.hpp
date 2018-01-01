//
// Created by Lou Landry on 31/12/2017.
//

#ifndef IMACMAN_DROPPABLE_HPP
#define IMACMAN_DROPPABLE_HPP

#include "GameElement.hpp"

class Droppable : public GameElement{
public:
    void render(glm::vec2);
    void drop(CactusMan &player);
};


#endif //IMACMAN_DROPPABLE_HPP
