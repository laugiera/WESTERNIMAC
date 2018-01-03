//
// Created by Lou Landry on 02/01/2018.
//

#include "GameApp.hpp"


GameApp::GameApp(const std::string &appPath) : appPath(appPath),
                                               cam2D(new Camera2D),
                                               camFPS(new CameraFPS),
                                               windowManager(Utils::windowWidth, Utils::windowHeight, "GLImac")
{
    OpenGlManager::getInstance().init(appPath.c_str());
    boardPath = Tools::getFolderPath(appPath) + "/data/board01.txt";
    gameboard = GameBoard(boardPath);
    currentCam = camFPS;

}

void GameApp::appLoop() {
    int rightPressed = 0;
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) {
                    currentCam->moveLeft(2.0);
                } else if (e.key.keysym.sym == SDLK_RIGHT) {
                    currentCam->moveLeft(-2.0);
                } else if (e.key.keysym.sym == SDLK_UP) {
                    currentCam->moveFront(2.0);
                } else if (e.key.keysym.sym == SDLK_DOWN) {
                    currentCam->moveFront(-2.0);
                } else if (e.key.keysym.sym == SDLK_c) {
                    if (currentCam == cam2D)
                        currentCam = camFPS;
                    else if (currentCam == camFPS)
                        currentCam = cam2D;
                }
            } else if (e.wheel.y == 1)
                currentCam->moveFront(1);
            else if (e.wheel.y == -1)
                currentCam->moveFront(-1);
            else if (e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        gameboard.render();
        glm::mat4 viewMatrix = currentCam->getViewMatrix();
        OpenGlManager::getInstance().drawAll(windowManager,viewMatrix);
    }

}

GameApp::~GameApp() {
    currentCam = nullptr;
    delete(cam2D);
    delete(camFPS);
}
