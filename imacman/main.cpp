//
// Created by Lou Landry on 04/11/2017.
//

/*
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
}*/
#include <SDL2/SDL.h>


int main(int argc, char* argv[]){


    SDL_Init(SDL_INIT_AUDIO);
    // load WAV file

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    SDL_LoadWAV("sounds/test.wav", &wavSpec, &wavBuffer, &wavLength);

    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

    // play audio
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    // keep application running long enough to hear the sound

    SDL_Delay(300000);

    // clean up

    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();

    return 0;

}