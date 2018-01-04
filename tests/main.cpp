//
// Created by Amel on 26/12/2017.
//

#include <iostream>
#include <GL/glut.h>
#include <glimac/SDL2WindowManager.hpp>
//#include "../dependencies/SDL2/include/SDL2/SDL_mixer.h"
#include <SDL2/SDL_mixer.h>


using namespace glimac;

enum {
    SRF_MenuPlay, SRF_MenuInstructions, SRF_MenuQuit,
    SRF_Instructions,
    SRF_COUNT
};

enum {
    TXT_MenuPlay, TXT_MenuInstructions, TXT_MenuQuit,
    TXT_Instructions,
};

// State.
enum {
    ST_Menu, ST_Play, ST_Instructions
};

typedef struct Opt
{
    int nbr_joueur ;
    int theme;
    int etat_du_jeu;//0 menu; 1 jeu; 2 game over; -1 stop
    int deces; //le joueur perdant

}Opt;



// Surface names.
int LoadSurfaces(SDL_Surface* surfaces[SRF_COUNT])
{
    surfaces[SRF_MenuPlay] = SDL_LoadBMP("images/menu/MMP.bmp");
    surfaces[SRF_MenuInstructions] = SDL_LoadBMP("images/menu/MMI.bmp");
    surfaces[SRF_MenuQuit] = SDL_LoadBMP("images/menu/MMQ.bmp");
    surfaces[SRF_Instructions] = SDL_LoadBMP("images/menu/INS.bmp");

    int i;
    for (i = 0; i < SRF_COUNT; ++i)
    {
        if (surfaces[i] == NULL)
        {
            fprintf(stderr, "Unable to load surface n°%d.\n", i + 1);
            return 0;
        }
    }

    return 1;
}

int LoadTextures(SDL_Texture* textures[SRF_COUNT], SDL_Renderer * renderer)
{

    SDL_Surface* surfaces[SRF_COUNT];
    if (!LoadSurfaces(surfaces))
    {
        return EXIT_FAILURE;
    }

    int i;
    for (i = 0; i < SRF_COUNT; ++i)
    {
        if (surfaces[i] == NULL)
        {
            fprintf(stderr, "Unable to load surface n°%d.\n", i + 1);
            return 0;
        }
    }


    SDL_CreateTextureFromSurface(renderer, surfaces[SRF_MenuPlay]);


    textures[TXT_MenuPlay] = SDL_CreateTextureFromSurface(renderer, surfaces[SRF_MenuPlay]);
    textures[TXT_MenuInstructions] = SDL_CreateTextureFromSurface(renderer, surfaces[SRF_MenuInstructions]);
    textures[TXT_MenuQuit] = SDL_CreateTextureFromSurface(renderer, surfaces[SRF_MenuQuit]);
    textures[TXT_Instructions] = SDL_CreateTextureFromSurface(renderer, surfaces[SRF_Instructions]);


    for (i = 0; i < SRF_COUNT; ++i)
    {
        SDL_FreeSurface(surfaces[i]);
    }

    return 1;
}



int main(int argc, char** argv)
{


    int i;
    int srfIdx=0;

    int loop1 = 1;
    int state = ST_Menu;
    int menuIdx = 0, playIdx = 0;

    //Set up screen
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("WESTERNIMAC",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture* textures[SRF_COUNT];

    LoadTextures(textures, renderer);

    Mix_Chunk *MMusic;
    MMusic= Mix_LoadWAV("sons/MMSong.wav"); //Chargement de la musique du fond
    Mix_Chunk *KMusic = Mix_LoadWAV("sons/KeySound.wav"); //Chargement du son touche
    Mix_PlayChannel(1, MMusic, -1);

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

        //Apply image to screen

        //Update Screen


        SDL_RenderCopy(renderer, textures[srfIdx], NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                loop1 = 0;
                //config->etat_du_jeu=-1;
                break;
            }

            switch (e.type)
            {
                case SDL_KEYDOWN:
                   /* if(Mix_Paused(1) == 0)  //play only when sound not muted
                     {
                         Mix_PlayChannel(2, KMusic, 0);
                     }*/

                    switch (e.key.keysym.sym)
                    {
                        case SDLK_UP:
                        {
                            if (state == ST_Menu)
                            {
                                menuIdx = (3 + menuIdx - 1) % 3;

                            }
                            break;
                        }
                        case SDLK_DOWN:
                        {
                            if (state == ST_Menu)
                            {
                                menuIdx = (menuIdx + 1) % 3;

                            }
                            break;
                        }

                        case SDLK_RETURN:
                        {
                            if (state == ST_Menu)
                            {
                                if (menuIdx == 0 )
                                {
                                    state = ST_Play;


                                }
                                else if (menuIdx == 1)
                                {
                                    state = ST_Instructions;

                                }
                                else if (menuIdx == 2)
                                {

                                    //config->etat_du_jeu=-1;
                                    loop1 = 0;
                                }
                            }

                            if (state == ST_Play)
                            {


                            }
                            break;
                        }
                        case SDLK_p:
                        {
                            if (state == ST_Play)
                            {
                                //Mix_Resume(1);
                                if (playIdx ==0 )
                                {
                                    //config->theme=1;
                                    //config->etat_du_jeu=1;
                                    loop1=0;
                                }
                                else if (playIdx == 1)
                                {
                                    //config->theme=2;
                                    //config->etat_du_jeu=1;
                                    loop1=0;
                                }
                            }
                            break;
                        }
                        case SDLK_m:
                        {
                            /* if(Mix_Paused(1) == 1)
                             {
                                 Mix_Resume(1);
                             }
                             else
                             {
                                 Mix_Pause(1);
                             }
                             break;*/
                        }
                        case SDLK_ESCAPE :
                            loop1 = 0;
                            //config->etat_du_jeu=-1;
                            break;

                        case SDLK_BACKSPACE:
                        {
                            state = ST_Menu;
                            break;
                        }

                        default:
                            break;
                    }
            }
        }

    }
    //Free the loaded image
    for (i = 0; i < SRF_COUNT; ++i)
    {
        SDL_DestroyTexture(textures[i]);
    }

   /* SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(MMusic); //Libération de la musique
    Mix_FreeChunk(KMusic); //Libération de la musique
    Mix_CloseAudio(); //Fermeture de l'API*/

    return 0;
}

