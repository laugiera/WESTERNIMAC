//
// Created by Amel on 9/1/2018.
//

#ifndef IMACMAN_SAVE_HPP
#define IMACMAN_SAVE_HPP

#include "CactusMan.hpp"

class Save {

    Save();
    ~Save();

public:
    void saveGame(CactusMan &player, std::vector<std::vector<Tile*>> TileMatrix);


};


#endif //IMACMAN_SAVE_HPP
