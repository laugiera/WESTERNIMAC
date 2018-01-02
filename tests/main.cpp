//
// Created by Lou on 16/12/2017.
//

#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <memory>
#include <vector>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/SDL2WindowManager.hpp>


#include "OpenGlManager.hpp"

using namespace glimac;

int main(int argc, char** argv) {
    glimac::FilePath applicationPath(argv[0]);
    glimac::SDLWindowManager windowManager(Utils::windowWidth, Utils::windowHeight, "GLImac");
    OpenGlManager manager = OpenGlManager();
    manager.init(argv[0]);
    RenderModel renderCube = RenderModel("../../tests/models/cube",applicationPath,"3D2", "directionallight");
    manager.addRenderModel(&renderCube);

    TrackballCamera camera;

    /**APPLICATION LOOP***/
    int rightPressed = 0;
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_LEFT){
                    //Camera.moveLeft(2.0); if freeflycam
                }
                else if(e.key.keysym.sym == SDLK_RIGHT){
                   // Camera.moveLeft(-2.0); if freeflycam
                }
                else if(e.key.keysym.sym == SDLK_UP){
                    camera.moveFront(2.0);
                }
                else if(e.key.keysym.sym == SDLK_DOWN){
                    camera.moveFront(-2.0);
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_RIGHT){
                    rightPressed = 1;
                }
            }
            else if(e.wheel.y == 1 )
                camera.moveFront(1);
            else if(e.wheel.y == -1)
                camera.moveFront(-1);
            else if(e.type == SDL_MOUSEBUTTONUP) {
                if(e.button.button == SDL_BUTTON_RIGHT){
                    rightPressed = 0;
                }
            }
            else if (e.type == SDL_MOUSEMOTION && rightPressed == 1){
                camera.rotateLeft(e.motion.xrel);
                camera.rotateUp(e.motion.yrel);
            }

            else if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        glm::mat4 viewMatrix = camera.getViewMatrix();
        manager.drawAll(windowManager,viewMatrix);
    }

    //everything is deleted automatically

    return EXIT_SUCCESS;
}
