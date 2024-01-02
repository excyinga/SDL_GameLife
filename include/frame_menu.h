#ifndef _FRAME_MENU_H_
#define _FRAME_MENU_H_
#pragma once

#include <SDL2/SDL.h>

#include "types.h"

#define MENU_FRAMES_AMOUNT 100

typedef enum
{
	NOT_CLICKED,
	NEW_GAME_BUTTON,
	SETTINGS,
	EXITING
} game_menu_button;

typedef struct
{
	struct
	{
		int x;
		int y;
	} position;
	
	game_menu_button clicked_button;

} menu_events;

extern SDL_Surface * array_of_menu_frames[];
extern game_menu_button menu_clicked_button;

#endif