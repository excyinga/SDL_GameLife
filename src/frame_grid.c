#include <SDL2/SDL.h>

#include "application.h"

#include "tools.h"
#include "types.h"

void ClearScreen(application_t * application);

void ClearScreen(application_t * application)
{	
	SDL_Color bg_color = {0, 0, 0};

	for (int i = 0; i < application->surface->w * application->surface->h; i++)
		((int *) application->surface->pixels)[i] = * (int *) &bg_color;

	return;
}
void GridDrawing(application_t * application, uint_16 grid_amount)
{
	ClearScreen(application);

	SDL_Color grid_color = {0, 255, 255};

	const int GRID_STEP_X = application->surface->w / grid_amount;
	const int GRID_STEP_Y = application->surface->h / grid_amount;

	// Drawing vertical grids
	for (uint_32 y = 0; y < application->surface->h; y++)
	{
		for (uint_32 grid_counter = 0; grid_counter <= grid_amount; grid_counter++)
		{
			if (grid_counter == grid_amount)
				SetPixel(application->surface, grid_counter * GRID_STEP_X - 1, y, grid_color);
			else
				SetPixel(application->surface, grid_counter * GRID_STEP_X, y, grid_color);
		}
	}

	//Drawing horizontal grids
	for (uint_32 grid_counter = 0; grid_counter <= grid_amount; grid_counter++)
	{
		for (uint_32 x = 0; x < application->surface->w; x++)
		{
			if (grid_counter == grid_amount)
				SetPixel(application->surface, x, GRID_STEP_Y * grid_counter - 1, grid_color);
			else
				SetPixel(application->surface, x, GRID_STEP_Y * grid_counter, grid_color);
		}
	}

	return;
}