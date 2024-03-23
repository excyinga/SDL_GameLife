#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#pragma once

#include <SDL2/SDL.h>

#include "types.h"

#define APP_WINDOW_WIDTH    1920
#define APP_WINDOW_HEIGHT   1080

#define GRID_AMOUNT 10

typedef struct application_t application_t;

typedef struct
{
    int size;
    bool * cells;
} grid_data;

struct application_t
{
    SDL_Window * window;
    SDL_Surface * surface;

    struct 
    {
        struct
        {
            int x;
            int y;
        } position;

        bool clicked : 1;
    } game_events;

    enum scene
    {
        GAME_LOADING = 0,
        GAME_MENU,
        GAME_GRID,
        GAME_EXITING
    } scene;

    grid_data my_grid;
};

void FrameGameLoading(application_t * application);
void FrameMenu(application_t * application);
void FrameGrid(application_t * application);
grid_data AllocGridData(int size);
bool GetCell(int x, int y, grid_data data);
void SetCell(int x, int y, bool state, grid_data data);

extern bool _game_routine;

#endif