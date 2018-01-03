//
// Created by Lou Landry on 31/12/2017.
//

#ifndef IMACMAN_WALL_HPP
#define IMACMAN_WALL_HPP

#include "GameElement.hpp"

class Wall : public GameElement{
public:
    void render(glm::vec2);
    void drop(CactusMan &player);
    void createRenderModel();
};


#endif //IMACMAN_WALL_HPP
