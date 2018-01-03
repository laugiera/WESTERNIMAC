//
// Created by Lou Landry on 02/01/2018.
//

#ifndef IMACMAN_GAMEAPP_HPP
#define IMACMAN_GAMEAPP_HPP

#include "GameBoard.hpp"


class GameApp {
public:
    GameApp() = default;

    GameApp(const std::string &appPath);

    void gameLoop();


private:
    GameBoard gameboard;
    std::string boardPath;
    std::string appPath;

};


#endif //IMACMAN_GAMEAPP_HPP
