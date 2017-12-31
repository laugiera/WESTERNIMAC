//
// Created by Lou Landry on 30/12/2017.
//

#ifndef IMACMAN_GAMEBOARD_HPP
#define IMACMAN_GAMEBOARD_HPP

#include "Tile.hpp"
#include <string>
#include "BoardLoader.hpp"


class Gameboard {
public:
    Gameboard(const std::string &boardPath);

    void loadBoard();

private:
    //Player player;
    std::vector<std::vector<Tile>> tiles;
    std::string boardPath;

};


#endif //IMACMAN_GAMEBOARD_HPP
