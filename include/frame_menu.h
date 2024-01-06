#ifndef _FRAME_MENU_H_
#define _FRAME_MENU_H_
#pragma once

#include <SDL2/SDL.h>

#include "types.h"

#define MENU_FRAMES_AMOUNT 100

typedef enum game_menu_button game_menu_button;

typedef struct menu_events_t menu_events_t;

enum game_menu_button
{
	NOT_CHOSE,
	NEW_GAME_BUTTON,
	SETTINGS_BUTTON,
	EXITING_BUTTON
};

extern SDL_Surface * array_of_menu_frames[];

extern game_menu_button menu_clicked_button;

#endif