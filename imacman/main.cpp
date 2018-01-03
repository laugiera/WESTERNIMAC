//
// Created by Lou Landry on 04/11/2017.
//

#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <memory>
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/SDL2WindowManager.hpp>
#include "GameApp.hpp"
#include "Camera2D.hpp"
#include "CameraFPS.hpp"

using namespace glimac;

int main(int argc, char** argv) {

    glimac::SDLWindowManager windowManager(Utils::windowWidth, Utils::windowHeight, "GLImac");
    GameApp app(argv[0]);

    CameraFPS *cameraFPS = new CameraFPS();
    Camera2D *camera2D = new Camera2D();
    Camera *currentCamera = cameraFPS;

    /**APPLICATION LOOP***/
    int rightPressed = 0;
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_LEFT){
                    currentCamera->moveLeft(2.0);
                }
                else if(e.key.keysym.sym == SDLK_RIGHT){
                    currentCamera->moveLeft(-2.0);
                }
                else if(e.key.keysym.sym == SDLK_UP){
                    currentCamera->moveFront(2.0);
                }
                else if(e.key.keysym.sym == SDLK_DOWN){
                    currentCamera->moveFront(-2.0);
                }
                else if(e.key.keysym.sym == SDLK_c){
                    if(currentCamera == camera2D)
                        currentCamera = cameraFPS;
                    else if(currentCamera == cameraFPS)
                        currentCamera = camera2D;
                }
            }
            else if(e.wheel.y == 1 )
                currentCamera->moveFront(1);
            else if(e.wheel.y == -1)
                currentCamera->moveFront(-1);
            else if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        app.gameLoop();
        glm::mat4 viewMatrix = currentCamera->getViewMatrix();
        OpenGlManager::getInstance().drawAll(windowManager,viewMatrix);
    }

    currentCamera = nullptr;
    delete(camera2D);
    delete(cameraFPS);

    return EXIT_SUCCESS;
}