//
// Created by Lou on 16/12/2017.
//

#define GLEW_STATIC
#include <glimac/SDL2WindowManager.hpp>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <memory>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <Texture.hpp>
#include <vector>
#include "RenderModel.h"
#include "Light.h"

using namespace glimac;


int main(int argc, char** argv) {
    /***** SDL THINGY *****/
    // Initialize SDL and open a window
    SDLWindowManager windowManager(1000, 800, "GLImac");
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);
    glEnable(GL_DEPTH_TEST);


    /***** VARIABLES *****/
    glcustom::GPUProgram program = glcustom::GPUProgram(applicationPath,"3D2", "directionallight");
    RenderModel renderCube = RenderModel("../imacman/models/cube");
    Light light = Light(glm::vec3(0.8),glm::vec3(1),glm::vec3(1));

    light.addLightUniforms(program);
    renderCube.addModelUniforms(program);

    program.use();

    /***CAMERA***/
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


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5, 0.5, 0.5, 1);

        //transformation
        renderCube.setModelMatrix();

        glm::mat4 rotation = glm::rotate(glm::mat4(1.f), windowManager.getTime(), glm::vec3(0, 1, 0));
        glm::mat4 scale = glm::scale(glm::mat4(1.f),glm::vec3(0.1f));
        glm::mat4 viewMatrix = camera.getViewMatrix();

        light.setDirection();
        rotation = glm::rotate(glm::mat4(1.f), windowManager.getTime()+100, glm::vec3(0, 1, 0));
        light.transform(rotation);
        light.transform(viewMatrix);
        light.sendLightUniforms(program);

        renderCube.transform(scale * rotation);
        renderCube.render(viewMatrix,program);

        // Update the display
        windowManager.swapBuffers();
    }

    //everything is deleted automatically

    return EXIT_SUCCESS;
}
