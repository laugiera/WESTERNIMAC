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
#include "include/ObjectModel.hpp"
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Geometry.hpp>
#include <VAO.hpp>
#include <GPUProgram.hpp>
#include <Texture.hpp>
#include <vector>

using namespace glimac;


int disablemain(int argc, char** argv) {
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

    /***** GPU PROGRAM *****/

    glcustom::GPUProgram program(applicationPath, "3D2",  "directionallight");
    std::vector<std::string> uniform_variables = {"uMVPMatrix", "uMVMatrix","uNormalMatrix","uKd","uKs","uShininess","uLightDir_vs","uLightIntensity"};
    program.addUniforms(uniform_variables);
    program.use();

    //variables globales
    glm::mat4 ProjMat, MVMatrix, NormalMatrix;

    //ObjectModel cube1 = ObjectModel("sould raise exception");
    ObjectModel cube = ObjectModel("../imacman/models/cube");


    Sphere sphere = Sphere(1,32,16);
    std::vector<ShapeVertex> objectVertices;
    for(int i = 0; i< sphere.getVertexCount(); i++){
        objectVertices.push_back(sphere.getDataPointer()[i]);
    }


    /***** BUFFERS *****/
    glcustom::VBO vbo = glcustom::VBO();
    glcustom::IBO ibo = glcustom::IBO();
    glcustom::VAO vao = glcustom::VAO();


    vbo.fillBuffer(cube.getVertices_vector());
    ibo.fillBuffer(cube.getIndices_vector());
    vao.fillBuffer(cube.getVertices_vector(), &vbo, &ibo);

    glcustom::VBO vboSphere = glcustom::VBO();
    glcustom::VAO vaoSphere = glcustom::VAO();

    vboSphere.fillBuffer(objectVertices);
    vaoSphere.fillBuffer(objectVertices, &vboSphere);

    glEnable(GL_DEPTH_TEST);


    /***CAMERA***/
    TrackballCamera Camera;

    // Application loop:
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
                    Camera.moveFront(2.0);
                }
                else if(e.key.keysym.sym == SDLK_DOWN){
                    Camera.moveFront(-2.0);
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_RIGHT){
                    rightPressed = 1;
                }
            }
            else if(e.wheel.y == 1 )
                Camera.moveFront(1);
            else if(e.wheel.y == -1)
                Camera.moveFront(-1);
            else if(e.type == SDL_MOUSEBUTTONUP) {
                if(e.button.button == SDL_BUTTON_RIGHT){
                    rightPressed = 0;
                }
            }
            else if (e.type == SDL_MOUSEMOTION && rightPressed == 1){
                Camera.rotateLeft(e.motion.xrel);
                Camera.rotateUp(e.motion.yrel);
            }

            else if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5, 0.5, 0.5, 1);

        //transformation
        ProjMat = glm::perspective(glm::radians(70.f), 1000.f/800.f, 0.1f, 100.f);
        glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,5));
        ModelMatrix = glm::scale(ModelMatrix,glm::vec3(0.2f));
        glm::mat4 ViewMatrix = Camera.getViewMatrix();
        glm::mat4 MV = ViewMatrix * ModelMatrix;
        MV = glm::rotate(MV, windowManager.getTime(), glm::vec3(0, 1, 0));
        glm::mat4 MVP = ProjMat * MV;
        NormalMatrix = glm::transpose(glm::inverse(MV));


        program.sendUniformMat4("uMVPMatrix", MVP);
        program.sendUniformMat4("uMVMatrix", MV);
        program.sendUniformMat4("uNormalMatrix", NormalMatrix);

        //light
        glm::vec4 lightPosition = glm::vec4(1,2,1,1);
        glm::vec4 lightDirection = glm::vec4(1,1,0,0);
        glm::mat4 rotation = glm::rotate(glm::mat4(1),windowManager.getTime()+50,glm::vec3(0,1,0));
        //lightPosition = rotation * lightPosition;
        lightPosition = ViewMatrix * lightPosition;
        lightDirection = ViewMatrix * lightDirection;

        program.sendUniform1f("uShininess", 64);
        //program.sendUniformVec4("uLightPos_vs",lightPosition);
        program.sendUniformVec4("uLightDir_vs",lightDirection);
        program.sendUniformVec3("uKd",glm::vec3(1));
        program.sendUniformVec3("uKs",glm::vec3(0.8));
        program.sendUniformVec3("uLightIntensity",glm::vec3(1,1,1));

        //draw cube
        vao.bind();
        glDrawElements(GL_TRIANGLES, cube.getIndices_vector().size(), GL_UNSIGNED_INT, 0);
        vao.debind();

        //sphere
        ModelMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(3,0,5));
        MV = ViewMatrix * ModelMatrix;
        MVP = ProjMat * MV;
        NormalMatrix = glm::transpose(glm::inverse(MV));
        program.sendUniformMat4("uMVPMatrix", MVP);
        program.sendUniformMat4("uMVMatrix", MV);
        program.sendUniformMat4("uNormalMatrix", NormalMatrix);
        vaoSphere.bind();
        glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());
        vaoSphere.debind();


        // Update the display
        windowManager.swapBuffers();
    }

    //everything is deleted automatically

    return EXIT_SUCCESS;
}
