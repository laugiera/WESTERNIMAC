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
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Geometry.hpp>
#include <VAO.hpp>
#include <GPUProgram.hpp>
#include <Texture.hpp>
#include <vector>

/***
 * La map fait un carré de 100 par 100
 *
 *
 */


using namespace glimac;


int main(int argc, char** argv) {
    /***** SDL THINGY *****/
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

    FilePath applicationPath(argv[0]);

    /***** GPU PROGRAM *****/

    glcustom::GPUProgram program(applicationPath, "light",  "directLight");
    std::vector<std::string> uniform_variables = {"MV", "MVP","V","M","LightPosition_worldspace",
                                                 "rotation"};
    program.addUniforms(uniform_variables);
    program.use();

    //variables globales
    glm::mat4 ProjMat, MVMatrix, NormalMatrix;

    Geometry teapot;
    teapot.loadOBJ("../imacman/models/teapot.obj","",true);

    glimac::ShapeVertex vertices[teapot.getVertexCount()];
    for (int i = 0; i < teapot.getVertexCount(); ++i) {
        vertices[i].position = teapot.getVertexBuffer()[i].m_Position;
        vertices[i].normal = teapot.getVertexBuffer()[i].m_Normal;
        vertices[i].texCoords = teapot.getVertexBuffer()[i].m_TexCoords;
    }
    std::vector<glimac::ShapeVertex> vertices_vector(vertices, vertices+teapot.getVertexCount()-1);

    uint32_t indices[teapot.getIndexCount()];
    std::vector<uint32_t> indices_vector(teapot.getIndexBuffer(), teapot.getIndexBuffer()+teapot.getIndexCount()-1);
    for (int i = 0; i < teapot.getIndexCount(); ++i) {
        indices[i] = teapot.getIndexBuffer()[i];
    }

    /***** BUFFERS *****/
    glcustom::VBO vbo = glcustom::VBO();
    glcustom::IBO ibo = glcustom::IBO();
    glcustom::VAO vao = glcustom::VAO();

    vbo.fillBuffer(vertices_vector);
    ibo.fillBuffer(indices_vector);
    vao.fillBuffer(vertices_vector, &vbo, &ibo);

    /***CAMERA***/
    FreeflyCamera Camera;

    // Application loop:
    int rightPressed = 0;
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_LEFT){
                    Camera.rotateLeft(5.0);
                }
                else if(e.key.keysym.sym == SDLK_RIGHT){
                    Camera.rotateLeft(-5.0);
                }
                else if(e.key.keysym.sym == SDLK_UP){
                    Camera.rotateUp(5.0);
                }
                else if(e.key.keysym.sym == SDLK_DOWN){
                    Camera.rotateUp(-5.0);
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_RIGHT){
                    rightPressed = 1;
                }
            }
            else if(e.wheel.y == 1 )
                Camera.moveFront(-1);
            else if(e.wheel.y == -1)
                Camera.moveFront(1);
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


        glClear(GL_COLOR_BUFFER_BIT);


        ProjMat = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        glm::mat4 MobelMatrix = glm::translate(glm::mat4(1.0f) , glm::vec3(0.f,-5.f,-10.f));
        glm::mat4 ViewMatrix = Camera.getViewMatrix();
        glm::mat4 MV = ViewMatrix * MobelMatrix;
        glm::mat4 MVP = ProjMat * MV;

        glm::vec4 lightPos = glm::vec4(200,200,500,1);
        glm::mat4 rotation = glm::rotate(glm::mat4(1),windowManager.getTime(),glm::vec3(0,1,0));
        //lightPos = lightPos * rotation;

        //send uniform variables
        program.sendUniformMat4("V", ViewMatrix);
        program.sendUniformMat4("M", MobelMatrix);
        program.sendUniformMat4("MV", MV);
        program.sendUniformMat4("MVP", MVP);
        program.sendUniformVec4("LightPosition_worldspace", lightPos);
        program.sendUniformMat4("rotation",rotation);

        //draw
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices_vector.size(), GL_UNSIGNED_INT, 0);
        vao.debind();


        // Update the display
        windowManager.swapBuffers();
    }

    //everything is deleted automatically

    return EXIT_SUCCESS;
}
