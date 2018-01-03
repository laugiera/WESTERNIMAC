//
// Created by Lou Landry on 31/12/2017.
//

#ifndef IMACMAN_FRUIT_HPP
#define IMACMAN_FRUIT_HPP

#include "Droppable.hpp"

class Fruit : public Droppable {

public:
    void drop(CactusMan &player);


};


#endif //IMACMAN_FRUIT_HPP
