//
// Created by Lou on 16/12/2017.
//

/*
#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <memory>
#include <vector>
#include "Camera2D.h"
#include "CameraFPS.h"
#include <glimac/SDL2WindowManager.hpp>
#include "OpenGlManager.hpp"

using namespace glimac;

int main(int argc, char** argv) {
    glimac::FilePath applicationPath(argv[0]);
    glimac::SDLWindowManager windowManager(Utils::windowWidth, Utils::windowHeight, "GLImac");
    OpenGlManager &manager = OpenGlManager::getInstance();
    manager.init(argv[0]);
    RenderModel renderCube = RenderModel("../../tests/models/cube",applicationPath,"3D2", "directionallight");
    manager.addRenderModel(&renderCube);

    CameraFPS *cameraFPS = new CameraFPS();
    Camera2D *camera2D = new Camera2D();
    Camera *currentCamera = cameraFPS;

    */
/**APPLICATION LOOP***//*

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
        glm::mat4 viewMatrix = currentCamera->getViewMatrix();
        manager.drawAll(windowManager,viewMatrix);
    }

    currentCamera = nullptr;
    delete(camera2D);
    delete(cameraFPS);

    return EXIT_SUCCESS;
}
*/
