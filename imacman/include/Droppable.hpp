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
    virtual int drop();
    virtual void createRenderModel();
};

class Fruit : public Droppable {
public:
    int drop(/*CactusMan &player*/);
};

class Gum : public Droppable{
public:
    int drop();
};

class SuperGum : public Droppable {
public:
    int drop();
    const bool &getMood() {return SuperMoodOn;}
private:
    bool SuperMoodOn=false; //set true when cactus can eat ghosts
};


#endif //IMACMAN_DROPPABLE_HPP
