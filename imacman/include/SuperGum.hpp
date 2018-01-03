//
// Created by Lou Landry on 31/12/2017.
//

#ifndef IMACMAN_SUPERGUM_HPP
#define IMACMAN_SUPERGUM_HPP

#include "Droppable.hpp"

class SuperGum : public Droppable {

public:
    void drop(CactusMan &player);

    const bool &getMood() {return SuperMoodOn;}

private:
    bool SuperMoodOn=false; //set true when cactus can eat ghosts
};


#endif //IMACMAN_SUPERGUM_HPP
