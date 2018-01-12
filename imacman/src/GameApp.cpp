//
// Created by Lou Landry on 02/01/2018.
//

#include "GameApp.hpp"

// State Main Menu
enum {
    ST_Menu, ST_Play, ST_Instructions
};


enum {
    SRF_MenuPlay, SRF_MenuInstructions, SRF_MenuQuit,
    SRF_Instructions,
    SRF_COUNT
};

enum {
    SRF_Save, SRF_Load, SRF_Exit,
    SRF_COUNT1
};


GameApp::GameApp(const std::string &appPath) : appPath(appPath),
                                               windowManager(Utils::windowWidth, Utils::windowHeight, "GLImac")
{
    OpenGlManager::getInstance().init(appPath.c_str());
    std::string filePath;
    if (loadMode){
        filePath =  "/data/saveGame.txt";
    }
    else filePath =  "/data/board02.txt";
    boardPath = Tools::getFolderPath(appPath) +filePath;
    try {
        gameboard = new GameBoard(boardPath);
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    saveMode=false;
    loadMode=false;
}

int GameApp::MainMenu(){

    int i;
    int srfIdx=0;
    int loop1 = 1;
    int state = ST_Menu;
    int menuIdx = 0;

    //load images paths
    std::string ImagesPaths[SRF_COUNT];

    ImagesPaths[SRF_MenuPlay] = "/images/menu/MMP.png";
    ImagesPaths[SRF_MenuInstructions] = "/images/menu/MMI.png";
    ImagesPaths[SRF_MenuQuit] = "/images/menu/MMQ.png";
    ImagesPaths[SRF_Instructions] = "/images/menu/INS.png";

    //SOUND
    SDL_Init(SDL_INIT_AUDIO);
    // load WAV file

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    SDL_LoadWAV("sounds/menu.wav", &wavSpec, &wavBuffer, &wavLength);

    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    // play audio
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    //show the cube with initial image
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    Camera2D camMenu = Camera2D();
    glm::mat4 viewMatrix;
    CubeMenu cubeMenu = CubeMenu();
    cubeMenu.createRenderModel();



    //pour changer la texture :
    bool stateChanged=false;
    while (loop1)
    {
        // Update surface.
        if (state == ST_Menu)
        {
            srfIdx = SRF_MenuPlay + menuIdx;
        }
        else if (state == ST_Instructions)
        {
            srfIdx = SRF_Instructions;
        }

        //Update Screen
        //update texture from table
        if(stateChanged){
            cubeMenu.getRenderModel()->setTexture(appFolderPath + ImagesPaths[srfIdx]);
            stateChanged= false;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            cubeMenu.render();
            cubeMenu.getRenderModel()->transform(glm::vec3(0),0,glm::vec3(1,0,0),glm::vec3(4.5));
            if (e.type == SDL_QUIT)
            {
                loop1 = 0;
                break;
            }

            switch (e.type)
            {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_UP:
                        {
                            if (state == ST_Menu)
                            {
                                menuIdx = (3 + menuIdx - 1) % 3;
                                stateChanged=true;
                            }
                            break;
                        }
                        case SDLK_DOWN:
                        {
                            if (state == ST_Menu)
                            {
                                menuIdx = (menuIdx + 1) % 3;
                                stateChanged=true;
                            }
                            break;
                        }

                        case SDLK_RETURN:
                        {
                            if (state == ST_Menu)
                            {
                                if (menuIdx == 0 )
                                {
                                    cubeMenu.getRenderModel()->transform(glm::vec3(0,1000,0), 0, glm::vec3(1,0,0), glm::vec3(1));
                                    SDL_CloseAudioDevice(deviceId);
                                    SDL_FreeWAV(wavBuffer);
                                    return ST_Play;
                                }
                                else if (menuIdx == 1)
                                {
                                    state = ST_Instructions;
                                    stateChanged=true;
                                }
                                else if (menuIdx == 2)
                                {
                                    loop1 = 0;
                                }
                            }
                            break;
                        }

                        case SDLK_BACKSPACE:
                        {
                            state = ST_Menu;
                            stateChanged=true;
                            break;
                        }

                        default:
                            break;
                    }
            }
            viewMatrix = camMenu.getViewMatrix();
            OpenGlManager::getInstance().drawMenu(windowManager,cubeMenu.getRenderModel(),viewMatrix);

        }

    }

}

int GameApp::PauseMenu(){

    int srfIdx=0;
    int loop1 = 1;
    int menuIdx = 0;

    //load images paths
    std::string ImagesPaths[SRF_COUNT1];

    ImagesPaths[SRF_Save] = "/images/menu/PMS.png";
    ImagesPaths[SRF_Load] = "/images/menu/PML.png";
    ImagesPaths[SRF_Exit] = "/images/menu/PMQ.png";

    //show the cube with initial image
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    Camera2D camMenu = Camera2D();
    glm::mat4 viewMatrix;
    CubeMenu cubeMenu = CubeMenu();
    cubeMenu.createRenderModel();
    cubeMenu.getRenderModel()->setTexture(appFolderPath + ImagesPaths[SRF_Save]);


    //pour changer la texture :
    bool stateChanged=false;
    while (loop1)
    {
        // Update surface.

        srfIdx =  menuIdx;

        //Update Screen
        //update texture from table
        if(stateChanged){
            cubeMenu.getRenderModel()->setTexture(appFolderPath + ImagesPaths[srfIdx]);
            stateChanged= false;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            cubeMenu.render();
            cubeMenu.getRenderModel()->transform(glm::vec3(0),0,glm::vec3(1,0,0),glm::vec3(4.48));

            if (e.type == SDL_QUIT)
            {
                loop1 = 0;
                break;
            }

            switch (e.type)
            {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_UP:
                        {
                            menuIdx = (3 + menuIdx - 1) % 3;
                            stateChanged=true;

                            break;
                        }
                        case SDLK_DOWN:
                        {
                            menuIdx = (menuIdx + 1) % 3;
                            stateChanged=true;
                            break;
                        }

                        case SDLK_RETURN:
                        {

                            if (menuIdx == 0 )
                            {
                                //save
                                cubeMenu.getRenderModel()->transform(glm::vec3(0,1000,0),0,glm::vec3(1,0,0),glm::vec3(1));
                                return ST_Play;
                            }
                            else if (menuIdx == 1)
                            {
                                //load
                                cubeMenu.getRenderModel()->transform(glm::vec3(0,1000,0),0,glm::vec3(1,0,0),glm::vec3(1));
                                return ST_Play;
                            }
                            else if (menuIdx == 2)
                            {
                                SDL_Quit();
                            }

                            break;
                        }

                        case SDLK_ESCAPE:
                        {
                            cubeMenu.getRenderModel()->transform(glm::vec3(0,1000,0),0,glm::vec3(1,0,0),glm::vec3(1));
                            return ST_Play;
                        }

                        default:
                            break;
                    }
            }
            viewMatrix = camMenu.getViewMatrix();
            OpenGlManager::getInstance().drawMenu(windowManager,cubeMenu.getRenderModel(),viewMatrix);

        }

    }

}


void GameApp::winLose(){

    int loop1 = 1;

    //SOUND
    SDL_Init(SDL_INIT_AUDIO);
    // load WAV file

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    //show the cube with initial image
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    Camera2D camMenu = Camera2D();
    glm::mat4 viewMatrix;
    CubeMenu cubeMenu = CubeMenu();
    cubeMenu.createRenderModel();

    if(win){
        cubeMenu.getRenderModel()->setTexture(appFolderPath + "/images/menu/win.jpg");
        SDL_LoadWAV("sounds/Win.wav", &wavSpec, &wavBuffer, &wavLength);

    }
    else{
    cubeMenu.getRenderModel()->setTexture(appFolderPath + "/images/menu/gameover.jpg");
        SDL_LoadWAV("sounds/Lose.wav", &wavSpec, &wavBuffer, &wavLength);

    }
    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    // play audio
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);


    while (loop1)
    {

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            cubeMenu.render();
            cubeMenu.getRenderModel()->transform(glm::vec3(0),0,glm::vec3(1,0,0),glm::vec3(4.48));

            if (e.type == SDL_QUIT)
            {
                loop1 = 0;
                break;
            }

            switch (e.type)
            {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {

                        case SDLK_ESCAPE:
                        {
                            cubeMenu.getRenderModel()->transform(glm::vec3(0,1000,0),0,glm::vec3(1,0,0),glm::vec3(1));
                            SDL_CloseAudioDevice(deviceId);
                            SDL_FreeWAV(wavBuffer);
                            appLoop();
                            loop1=0;
                            break;
                        }

                        default:
                            break;
                    }
            }
            viewMatrix = camMenu.getViewMatrix();
            OpenGlManager::getInstance().drawMenu(windowManager,cubeMenu.getRenderModel(),viewMatrix);

        }

    }

}

void GameApp::appLoop() {

    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    Plane2D lifePannel = Plane2D();
    lifePannel.createRenderModel();
    OpenGlManager::getInstance().addRenderModel(lifePannel.getRenderModel());
    lifePannel.getRenderModel()->setTexture(appFolderPath + "/textures/lifes3.png");

    Plane2D scorePannel = Plane2D();
    scorePannel.createRenderModel();
    OpenGlManager::getInstance().addRenderModel(scorePannel.getRenderModel());
    scorePannel.getRenderModel()->setTexture(appFolderPath + "/textures/score0.png");

    unsigned int lives, positionX, positionY, score;

    if (MainMenu() == ST_Play) {
        if (loadMode) {
            gameboard->updateScore("/data/saveGame.txt");
            // need to add line to reload the board
        }
        int rightPressed = 0;

        //SOUND
        SDL_Init(SDL_INIT_AUDIO);
        // load WAV file
        SDL_AudioSpec wavSpec;
        Uint32 wavLength;
        Uint8 *wavBuffer;
        SDL_LoadWAV("sounds/GameSong.wav", &wavSpec, &wavBuffer, &wavLength);
        // open audio device
        SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
        // play audio
        int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
        SDL_PauseAudioDevice(deviceId, 0);


        bool done = false;
        while (!done) {
            // Event loop:
            SDL_Event e;
            while (windowManager.pollEvent(e)) {

                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_q) {
                        gameboard->moveLeft();
                    } else if (e.key.keysym.sym == SDLK_d) {
                        gameboard->moveRight();
                    } else if (e.key.keysym.sym == SDLK_z) {
                        gameboard->moveUp();
                    } else if (e.key.keysym.sym == SDLK_s) {
                        gameboard->moveDown();
                    } else if (e.key.keysym.sym == SDLK_UP) {
                        gameboard->zoom();
                    } else if (e.key.keysym.sym == SDLK_DOWN) {
                        gameboard->dezoom();
                    } else if (e.key.keysym.sym == SDLK_c) {
                        gameboard->changeCamera();
                    } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                        if (PauseMenu() == ST_Play) {}
                    }
                } else if (e.wheel.y == 1)
                    gameboard->zoom();
                else if (e.wheel.y == -1)
                    gameboard->dezoom();
                else if (e.type == SDL_QUIT) {
                    done = true; // Leave the loop after this iteration
                }
            }
            //2D AND MENUS RENDERING
            if (gameboard->getCamFPS() != nullptr) {
                switch (gameboard->getPlayer()->getLives()) {
                    case 1:
                        lifePannel.getRenderModel()->setTexture(appFolderPath + "/textures/lifes1.png");
                        break;
                    case 2:
                        lifePannel.getRenderModel()->setTexture(appFolderPath + "/textures/lifes2.png");
                        break;
                    default:
                        break;

                }
                score = gameboard->getPlayer()->getScore();
                if (score > BoardLoader::getScoreMax() * (1 / 4.f)){
                    scorePannel.getRenderModel()->setTexture(appFolderPath + "/textures/score1.png");
                } else if (score > BoardLoader::getScoreMax() * (1 / 2.f)){
                    scorePannel.getRenderModel()->setTexture(appFolderPath + "/textures/score2.png");
                }else if (score > BoardLoader::getScoreMax() * (3 / 4.f)){
                    scorePannel.getRenderModel()->setTexture(appFolderPath + "/textures/score3.png");
                }

                positionX = gameboard->getPlayer()->getPosition().x;
                positionY = gameboard->getPlayer()->getPosition().y ;
                lifePannel.getRenderModel()->transform(glm::vec3(3+abs(positionX),3,-2+abs(positionY)),0,glm::vec3(1,0,0),glm::vec3(0.4,0.4,0.3));
                scorePannel.getRenderModel()->transform(glm::vec3(3+abs(positionX),3,-1+abs(positionY)),0,glm::vec3(1,0,0),glm::vec3(0.2,0.3,0.3));
            }
            else {
                lifePannel.getRenderModel()->transform(glm::vec3(10000),0,glm::vec3(1,0,0),glm::vec3(1));
                scorePannel.getRenderModel()->transform(glm::vec3(10000),0,glm::vec3(1,0,0),glm::vec3(1));
            }

            //GAME ELEMENT RENDERING
            gameboard->handleCamera();
            gameboard->handleGhosts();
            gameboard->handleCollisions();
            gameboard->render(windowManager);

            if(gameboard->hasWon())
            {
                win=true;
                SDL_CloseAudioDevice(deviceId);
                SDL_FreeWAV(wavBuffer);
                winLose();
            }
            else if(gameboard->hasLost())
            {
                win=false;
                SDL_CloseAudioDevice(deviceId);
                SDL_FreeWAV(wavBuffer);
                winLose();
            }
        }
        destroy();
             SDL_CloseAudioDevice(deviceId);
              SDL_FreeWAV(wavBuffer);
    }

}

GameApp::~GameApp() {
}

void GameApp::destroy() {
    gameboard->destroy();
    delete(gameboard);
}
