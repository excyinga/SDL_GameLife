#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#pragma once

#include <SDL2/SDL.h>

#include "types.h"

#define APP_WINDOW_WIDTH    1200
#define APP_WINDOW_HEIGHT   800

typedef enum scene scene;

typedef struct current_game_events current_game_events;
typedef struct application_t application_t;

enum scene
{
    GAME_LOADING = 0,
    GAME_MENU,
    GAME_GRID,
    GAME_EXITING
};

struct current_game_events
{
	struct
	{
		int x;
		int y;
	} position;

    bool clicked : 1;
};

struct application_t
{
    SDL_Window * window;
    SDL_Surface * surface;

    current_game_events game_events;

    scene current_scene;
};

void FrameGameLoading(application_t * application);
void FrameMenu(application_t * application);
void FrameGrid(application_t * application);

extern bool _game_routine;

#endif