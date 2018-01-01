//
// Created by Lou Landry on 30/12/2017.
//

#ifndef IMACMAN_GAMEBOARD_HPP
#define IMACMAN_GAMEBOARD_HPP

#include "Tile.hpp"
#include <string>
#include "BoardLoader.hpp"
#include "Ghost.hpp"
#include "CactusMan.hpp"


class GameBoard {
public:
    GameBoard(const std::string &boardPath);

    void loadBoard();

    void createGhosts();

    void createCactusman();

private:
    CactusMan player;
    std::vector<std::vector<Tile>> tiles;
    std::string boardPath;
    std::vector<Ghost*> ghosts;

};


#endif //IMACMAN_GAMEBOARD_HPP
