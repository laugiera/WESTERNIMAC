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
    GameApp app(argv[0]);
    app.appLoop();
    return EXIT_SUCCESS;
}