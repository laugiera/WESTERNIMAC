//
// Created by Lou Landry on 31/12/2017.
//

#ifndef IMACMAN_DROPPABLE_HPP
#define IMACMAN_DROPPABLE_HPP

#include "GameElement.hpp"
#include "OpenGlManager.hpp"


class Droppable : public GameElement{
public:
    void render(glm::vec2);
    virtual int drop() = 0;
    virtual void createRenderModel() = 0;
};

class Fruit : public Droppable {
public:
    int drop();
    void createRenderModel();
};

class Gum : public Droppable{
public:
    int drop();
    void createRenderModel();
};

class SuperGum : public Droppable {
public:
    int drop();
    void createRenderModel();
};


#endif //IMACMAN_DROPPABLE_HPP
