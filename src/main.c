#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "application.h"
#include "frame_menu.h"

#include "fonts.h"

#include "types.h"
#include "tools.h"

application_t application;

bool _game_routine = TRUE;

int main(void)
{
    //Init SDL components
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        printf("SDL_INIT error: %s\n", SDL_GetError());
        return 1;
    } 
    else if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_JPG | IMG_INIT_PNG))
    {
        printf("SDL_IMG error: %s\n", IMG_GetError());
        return 1;
    }
    else if (TTF_Init())
    {
        printf("SDL_TTF error: %s\n", TTF_GetError());
        return 1;
    }
    else if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        printf("SDL_MIXER error: %s\n", Mix_GetError());
        return 1;
    }
    
    extern application_t application;

    application.window = SDL_CreateWindow("Game of Life by Ol. K.", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (application.window == NULL)
    {
        printf("Window error: %s\n", SDL_GetError());
        return 1;
    }
    application.surface = SDL_GetWindowSurface(application.window);
    if (application.surface == NULL)
    {
        printf("Surface error: %s\n", SDL_GetError());
        return 1;
    }

    TTF_Font * font = TTF_OpenFont(path_to_font, FONT_SIZE);
    if (font == NULL)
    {
        printf("SDL_TTF open font error: %s\n", TTF_GetError());
        return 1;
    }

    // Routine of the game
/*     while (_game_routine)
    {
        FrameGameLoading(&application);
    }
 */
    return 0;
}
 
