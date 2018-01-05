//
// Created by Lou Landry on 02/01/2018.
//

#include "GameApp.hpp"


GameApp::GameApp(const std::string &appPath) : appPath(appPath),
                                               windowManager(Utils::windowWidth, Utils::windowHeight, "GLImac")
{
    OpenGlManager::getInstance().init(appPath.c_str());
    boardPath = Tools::getFolderPath(appPath) + "/data/board01.txt";
    try {
        gameboard = new GameBoard(boardPath);
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }



}

void GameApp::appLoop() {
    int rightPressed = 0;
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q){
                    gameboard->moveLeft();
                } else if (e.key.keysym.sym == SDLK_d){
                    gameboard->moveRight();
                } else if (e.key.keysym.sym == SDLK_z){
                    gameboard->moveUp();
                } else if (e.key.keysym.sym == SDLK_s){
                    gameboard->moveDown();
                } else if (e.key.keysym.sym == SDLK_UP){
                    gameboard->zoom();
                } else if (e.key.keysym.sym == SDLK_DOWN){
                    gameboard->dezoom();
                }
                else if (e.key.keysym.sym == SDLK_c) {
                    gameboard->changeCamera();
                }
            } else if (e.wheel.y == 1)
                gameboard->zoom();
            else if (e.wheel.y == -1)
                gameboard->dezoom();
            else if (e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        gameboard->handleCollisions();
        gameboard->render(windowManager);
        if(gameboard->hasWon() || gameboard->hasLost()) done = true;
    }
    destroy();

}

GameApp::~GameApp() {
}

void GameApp::destroy() {
    gameboard->destroy();
    delete(gameboard);
}
