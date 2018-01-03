//
// Created by Lou Landry on 02/01/2018.
//

#include "GameApp.hpp"


GameApp::GameApp(const std::string &appPath) : appPath(appPath)
{
    OpenGlManager::getInstance().init(appPath.c_str());
    boardPath = Tools::getFolderPath(appPath) + "/data/board00.txt";
    gameboard = GameBoard(boardPath);

}

void GameApp::gameLoop() {
    gameboard.render();

}
