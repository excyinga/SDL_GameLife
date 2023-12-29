#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#pragma once

#include <SDL2/SDL.h>

#define APP_WINDOW_WIDTH    1920
#define APP_WINDOW_HEIGHT   1080

typedef struct application_t application_t;

struct application_t 
{
    SDL_Window * window;
    SDL_Surface * surface;
};

void FrameGameLoading(application_t * application);
void FrameMenu(application_t * application);

#endif