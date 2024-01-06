#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#pragma once

#include <SDL2/SDL.h>

#include "types.h"

#define APP_WINDOW_WIDTH    1200
#define APP_WINDOW_HEIGHT   800

typedef enum scene scene;

typedef struct application_t application_t;

enum scene
{
    GAME_LOADING = 0,
    GAME_MENU,
    GAME_GRID,
    GAME_EXITING
};

struct application_t
{
    SDL_Window * window;
    SDL_Surface * surface;
};

void FrameGameLoading(application_t * application);
void FrameMenu(application_t * application);
void FrameGrid(application_t * application);

extern bool _game_routine;

extern scene current_scene;

#endif