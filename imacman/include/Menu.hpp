//
// Created by Amel on 10/1/2018.
//

#ifndef IMACMAN_MENU_HPP
#define IMACMAN_MENU_HPP
#include <glimac/SDL2WindowManager.hpp>

class Menu {
public:
    Menu();
    ~Menu();
    void MainMenu(SDL_Renderer * renderer);
    void PauseMenu();
    int LoadSurfacesMM(SDL_Surface* surfaces[]);
    int LoadSurfacesPM(SDL_Surface* surfaces[]);

    int LoadTexturesMM(SDL_Texture* textures[], SDL_Renderer * renderer);
    int LoadTexturesPM(SDL_Texture* textures[], SDL_Renderer * renderer);

    int getState(){return stateMenu;}
private:
    int stateMenu;
    bool loadMode;
    bool saveMode;


};


#endif //IMACMAN_MENU_HPP
