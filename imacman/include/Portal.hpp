//
// Created by Lou Landry on 31/12/2017.
//

#ifndef IMACMAN_ELEVATOR_HPP
#define IMACMAN_ELEVATOR_HPP

#include "GameElement.hpp"

class Portal : public GameElement{
public:
    void render(glm::vec2);
    int drop();
    void createRenderModel();
};


#endif //IMACMAN_ELEVATOR_HPP
