//
// Created by Lou Landry on 30/12/2017.
//

#include "../include/Gameboard.hpp"

Gameboard::Gameboard(const std::string &boardPath) : boardPath(boardPath) {}

void Gameboard::loadBoard() {
    BoardLoader boardLoader();
   // boardLoader().create
}
