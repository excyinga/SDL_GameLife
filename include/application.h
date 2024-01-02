#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#pragma once

#include <SDL2/SDL.h>

#include "types.h"

#define APP_WINDOW_WIDTH    1920
#define APP_WINDOW_HEIGHT   1080

typedef enum scene scene;

extern bool _game_routine;
extern scene current_scene;

enum scene
{
    GAME_LOADING = 0,
    GAME_MENU,
    GAME_GRID,
    GAME_EXITING
};

typedef struct
{
    SDL_Window * window;
    SDL_Surface * surface;
} application_t;

void FrameGameLoading(application_t * application);
void FrameMenu(application_t * application);
void FrameGrid(application_t * application);

#endif