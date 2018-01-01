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
#include "GameBoard.hpp"



using namespace glimac;

int main(int argc, char** argv) {
/*
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/


    GameBoard board = GameBoard(Tools::getFolderPath(argv[0]) + "/data/board01.txt");



    /*
    BoardLoader loader;
    std::vector<std::vector<Tile>> tiles = loader.createTileMatrix(
            "/Users/Lou/GoogleDrive/travail/IMAC2/S1/Programmation/Projets/WESTERNIMAC/tests/data/board01.txt");
    for(int i = 0; i<tiles.size(); i++){
        for(int j = 0; j<tiles[0].size(); j++){
            std::cout << tiles[i][j] << " ";
        }
        std::cout << std::endl;
    }
     */
/*
    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e{};
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        //std::cout << "test 1" << std::endl;
        // Update the display
//        windowManager.swapBuffers();
        //std::cout << "test 2" << std::endl;
 //   }

    return EXIT_SUCCESS;
}