#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "application.h"
#include "frame_loading.h"
#include "frame_menu.h"

#include "sound.h"
#include "fonts.h"

#include "types.h"
#include "tools.h"

#define ONE_FRAME_PER_SECOND 1000 / 60 

static application_t application;

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
    else if (Mix_OpenAudio(SOUND_FREQUENCY, SOUND_FORMAT, SOUND_CHANNELS, SOUND_CHUNKSIZE))
    {
        printf("SDL_Mixer OpenAudio erros: %s\n", Mix_GetError());
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
    music = Mix_LoadMUS(path_to_music);
    if (music == NULL)
    {
        printf("Music error: %s\n", Mix_GetError());
        return 1;
    }
    font = TTF_OpenFont(path_to_font, FONT_SIZE);
    if (font == NULL)
    {
        printf("SDL_TTF open font error: %s\n", TTF_GetError());
        return 1;
    }

    unsigned int t_s, t_m, t_e;

    // Routine of the game
    while (_game_routine)
    {
        t_s = SDL_GetTicks();

        if (loaded_frames_counter < MENU_FRAMES_AMOUNT)
            FrameGameLoading(&application);
        else
            FrameMenu(&application);

        SDL_UpdateWindowSurface(application.window);

        t_e = SDL_GetTicks();
        if (t_e - t_s < ONE_FRAME_PER_SECOND)
            SDL_Delay(ONE_FRAME_PER_SECOND - (t_e - t_s));
    }

    return 0;
}
 
