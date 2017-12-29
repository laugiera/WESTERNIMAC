#include <glimac/SDL2WindowManager.hpp>
#include <glimac/Sphere.hpp>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <VBO.hpp>
#include <VAO.hpp>
#include <GPUProgram.hpp>

using namespace glimac;



int disablemain(int argc, char** argv) {

    SDLWindowManager windowManager(600, 600, "GLImac");
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }


    //shaders
    FilePath applicationPath(argv[0]);

    glcustom::GPUProgram program(applicationPath, "3D2",  "directionallight");
    std::vector<std::string> uniform_variables = {"uMVPMatrix", "uMVMatrix","uNormalMatrix","uKd","uKs","uShininess","uLightDir_vs","uLightIntensity"};
    program.addUniforms(uniform_variables);
    program.use();


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    FreeflyCamera camera = FreeflyCamera();
    Sphere sphere = Sphere(1, 32, 16);

    glcustom::VBO vbo2 = glcustom::VBO();
    glcustom::VAO vao2 = glcustom::VAO();

    std::vector<ShapeVertex> objectVertices;
    for(int i = 0; i< sphere.getVertexCount(); i++){
        objectVertices.push_back(sphere.getDataPointer()[i]);
    }

    vbo2.fillBuffer(objectVertices);
    vao2.fillBuffer(objectVertices, &vbo2);


    //enable depth
    glEnable(GL_DEPTH_TEST);

    //angles de rotation
    std::vector<glm::vec3> angles_rotation_lunes;
    std::vector<float> angles_depart_lunes;
    for(int i = 0; i< 32; i++){
        angles_rotation_lunes.push_back(glm::sphericalRand(1.f));
        angles_depart_lunes.push_back(glm::linearRand(0.f, 180.f));
    }


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        //while(windowManager.pollEvent(e)) {
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            } else if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
                float relative_x = e.motion.xrel;
                float relative_y = e.motion.yrel;
                camera.rotateLeft(relative_x);
                camera.rotateUp(relative_y);

            } else if (windowManager.isKeyPressed(SDL_SCANCODE_UP)) {
                camera.rotateUp(30.f);
            } else if (windowManager.isKeyPressed(SDL_SCANCODE_DOWN)) {
                camera.rotateUp(-30.f);
            } else if (windowManager.isKeyPressed(SDL_SCANCODE_LEFT)) {
                camera.rotateLeft(30.f);
            } else if (windowManager.isKeyPressed(SDL_SCANCODE_RIGHT)) {
                camera.rotateLeft(-30.f);
            } else if (windowManager.isKeyPressed(SDL_SCANCODE_W)) {
                camera.moveFront(0.01);
            } else if (windowManager.isKeyPressed(SDL_SCANCODE_S)) {
                camera.moveFront(-0.01);
            } else if (windowManager.isKeyPressed(SDL_SCANCODE_A)) {
                camera.moveLeft(0.01);
            } else if (windowManager.isKeyPressed(SDL_SCANCODE_D)) {
                camera.moveLeft(-0.01);
            }

        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.01f,0.01f,0.03f,1.f);

        vao2.bind();
        glm::mat4 proj_matrix = glm::perspective(glm::radians(70.f), 1.f, 0.1f, 100.f);


        //
        program.use();

        glm::mat4 light_rotation = glm::rotate(glm::mat4(1), windowManager.getTime(), glm::vec3(0,1,0));
        glm::vec4  uLightDir_m = light_rotation * glm::vec4(1,1,0,0);
        glm::vec4  uLightDir_vs = (camera.getViewMatrix() *  uLightDir_m);

        program.sendUniformVec3("uKd",glm::vec3(0.5, 0.5, 1.f));
        program.sendUniformVec3("uKs",glm::vec3(0.5, 0.75, 1.f));
        program.sendUniform1f("uShininess", 64);
        program.sendUniformVec3("uLightDir_vs",glm::vec3( uLightDir_vs.x,  uLightDir_vs.y,  uLightDir_vs.z));
        program.sendUniformVec3("uLightIntensity",glm::vec3(1.f, 0.7, 0.f));


        //transfo
        glm::mat4   M_matrix,  MV_matrix,  normal_matrix,  MVP_matrix;
        M_matrix = glm::mat4(1.0);
        M_matrix = glm::translate( M_matrix, glm::vec3(0,0,5.f));
        M_matrix = glm::rotate( M_matrix, windowManager.getTime()/10, glm::vec3(0,1,0));
        MV_matrix = camera.getViewMatrix() *  M_matrix;
        normal_matrix = glm::transpose(glm::inverse( MV_matrix));
        MVP_matrix = proj_matrix *  MV_matrix;

        program.sendUniformMat4("uMVMatrix", MV_matrix);
        program.sendUniformMat4("uMVPMatrix", MVP_matrix);
        program.sendUniformMat4("uNormalMatrix", normal_matrix);


        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

/*
        for(int i = 0; i< 32; i++) {
            M_matrix = glm::mat4(1.0);
            M_matrix = glm::translate(M_matrix, glm::vec3(0,0,5));
            M_matrix = glm::rotate(M_matrix, angles_depart_lunes[i], angles_rotation_lunes[i]);
            M_matrix = glm::rotate(M_matrix, windowManager.getTime(), glm::vec3(0,1,0));
            M_matrix = glm::translate(M_matrix, glm::vec3(-2,0,0));
            M_matrix = glm::scale(M_matrix, glm::vec3(0.2, 0.2, 0.2));
            MV_matrix = camera.getViewMatrix() * M_matrix;
            MVP_matrix = proj_matrix * MV_matrix;
            normal_matrix = glm::transpose(glm::inverse(MV_matrix));

            program.sendUniformMat4("uMVMatrix",MV_matrix);
            program.sendUniformMat4("uMVPMatrix",MVP_matrix);
            program.sendUniformMat4("uNormalMatrix",normal_matrix);
            glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        }
*/
        vao2.debind();

        // Update the display
        windowManager.swapBuffers();
    }



    return EXIT_SUCCESS;
}
