#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#pragma once

#include <SDL2/SDL.h>

#define APP_WINDOW_WIDTH    1280
#define APP_WINDOW_HEIGHT   800 

typedef struct application_t application_t;

struct application_t 
{
    SDL_Window * window;
    SDL_Surface * surface;
};

#endif