//
// Created by Lou Landry on 02/01/2018.
//

#ifndef IMACMAN_GAMEAPP_HPP
#define IMACMAN_GAMEAPP_HPP

#include "GameBoard.hpp"
#include "Save.hpp"
#include "CubeMenu.hpp"



class GameApp {
public:
    GameApp() = default;

    GameApp(const std::string &appPath);

    virtual ~GameApp();

    void appLoop();

    void destroy();

    int MainMenu();
private:
    GameBoard * gameboard;
    std::string boardPath;
    std::string appPath;

    glimac::SDLWindowManager windowManager;

    //Save Saving;
    bool saveMode;
    bool loadMode;

};


#endif //IMACMAN_GAMEAPP_HPP
