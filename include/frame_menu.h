#ifndef _FRAME_MENU_H_
#define _FRAME_MENU_H_
#pragma once

#include <SDL2/SDL.h>

#include "application.h"

#define MENU_FRAMES_AMOUNT 1817

extern SDL_Surface * array_of_menu_frames[];

void FrameGameLoading(application_t *);

#endif