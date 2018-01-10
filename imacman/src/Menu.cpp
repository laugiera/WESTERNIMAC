//
// Created by Amel on 10/1/2018.
//

#include "Menu.hpp"

//surfaces for main menu
enum {
    SRF_MenuPlay, SRF_MenuInstructions, SRF_MenuQuit,
    SRF_Instructions,
    SRF_COUNT
};
//surfaces for pause menu
enum {
    SRF_Save, SRF_Load, SRF_Exit,
    SRF_COUNT1
};

//textures main menu
enum {
    TXT_MenuPlay, TXT_MenuInstructions, TXT_MenuQuit,
    TXT_Instructions,
};
//textures pause menu
enum {
    TXT_Save, TXT_Load, TXT_Exit,
};

// State Main Menu
enum {
    ST_Menu, ST_Play, ST_Instructions
};


Menu::Menu(){
    stateMenu = 0;
}

Menu:: ~Menu(){

}

// Surface names.
int Menu::LoadSurfacesMM(SDL_Surface* surfaces[SRF_COUNT])
{
    int i;
    surfaces[SRF_MenuPlay] = SDL_LoadBMP("images/menu/MMP.bmp");
    surfaces[SRF_MenuInstructions] = SDL_LoadBMP("images/menu/MMI.bmp");
    surfaces[SRF_MenuQuit] = SDL_LoadBMP("images/menu/MMQ.bmp");
    surfaces[SRF_Instructions] = SDL_LoadBMP("images/menu/INS.bmp");

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

int Menu::LoadSurfacesPM(SDL_Surface* surfaces[SRF_COUNT1])
{
    int i;

    surfaces[SRF_Save] = SDL_LoadBMP("images/menu/PMS.bmp");
    surfaces[SRF_Load] = SDL_LoadBMP("images/menu/PML.bmp");
    surfaces[SRF_Exit] = SDL_LoadBMP("images/menu/PMQ.bmp");

    for (i = 0; i < SRF_COUNT1; ++i)
    {
        if (surfaces[i] == NULL)
        {
            fprintf(stderr, "Unable to load surface n°%d.\n", i + 1);
            return 0;
        }
    }

    return 1;
}

int Menu::LoadTexturesMM(SDL_Texture* textures[SRF_COUNT], SDL_Renderer * renderer)
{

    SDL_Surface* surfaces[SRF_COUNT];
    if (!LoadSurfacesMM(surfaces))
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

int Menu::LoadTexturesPM(SDL_Texture* textures[SRF_COUNT1], SDL_Renderer * renderer)
{

    SDL_Surface* surfaces[SRF_COUNT1];
    if (!LoadSurfacesPM(surfaces))
    {
        return EXIT_FAILURE;
    }

    int i;
    for (i = 0; i < SRF_COUNT1; ++i)
    {
        if (surfaces[i] == NULL)
        {
            fprintf(stderr, "Unable to load surface n°%d.\n", i + 1);
            return 0;
        }
    }

    SDL_CreateTextureFromSurface(renderer, surfaces[SRF_Save]);
    textures[TXT_Save] = SDL_CreateTextureFromSurface(renderer, surfaces[SRF_Save]);
    textures[TXT_Load] = SDL_CreateTextureFromSurface(renderer, surfaces[SRF_Load]);
    textures[TXT_Exit] = SDL_CreateTextureFromSurface(renderer, surfaces[SRF_Exit]);

    for (i = 0; i < SRF_COUNT1; ++i)
    {
        SDL_FreeSurface(surfaces[i]);
    }

    return 1;
}


void Menu::MainMenu(SDL_Renderer * renderer){
    int i;
    int srfIdx=0;

    int loop1 = 1;
    int state = ST_Menu;
    int menuIdx = 0;

    //Set up screen
    /*SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("WESTERNIMAC",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 800, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
*/
    SDL_Texture* textures[SRF_COUNT];

    LoadTexturesMM(textures, renderer);


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

        SDL_RenderCopy(renderer, textures[srfIdx], NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
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
                                    stateMenu=1;
                                    loop1=0;
                                }
                                else if (menuIdx == 1)
                                {
                                    state = ST_Instructions;
                                }
                                else if (menuIdx == 2)
                                {
                                    loop1 = 0;
                                }
                            }
                            break;
                        }
                        case SDLK_ESCAPE :
                            loop1 = 0;
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
}

void Menu::PauseMenu() {
    int i;
    int srfIdx=0;

    int loop1 = 1;
    int menuIdx = 0;

    //Set up screen
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("WESTERNIMAC",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 800, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture* textures[SRF_COUNT1];

    LoadTexturesPM(textures, renderer);


    while (loop1)
    {
        // Update surface.

        srfIdx =  menuIdx;

        //Update Screen

        SDL_RenderCopy(renderer, textures[srfIdx], NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
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
                            break;
                        }
                        case SDLK_DOWN:
                        {
                            menuIdx = (menuIdx + 1) % 3;
                            break;
                        }

                        case SDLK_RETURN:
                        {
                            if (menuIdx == 0 )
                            {
                                saveMode=true;
                                stateMenu=2;
                                loop1=0;
                            }
                            else if (menuIdx == 1)
                            {
                                loadMode=true;
                                loop1=0;

                            }
                            else if (menuIdx == 2)
                            {
                                loop1 = 0;
                            }
                            break;
                        }
                        case SDLK_ESCAPE :
                            stateMenu=2;
                            loop1 = 0;
                            break;

                        default:
                            break;
                    }
            }
        }

    }
    //Free the loaded image
    for (i = 0; i < SRF_COUNT1; ++i)
    {
        SDL_DestroyTexture(textures[i]);
    }

}