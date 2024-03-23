#include <stdio.h>

#include <SDL2/SDL.h>

#include "application.h"

extern uint_16 loaded_frames_counter;

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

	SDL_Color grid_color = {255, 0, 0};
	SDL_Color cell_color = {.b = 0xFF};

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

	int padding = 1;
	SDL_Rect cell_coordinate_position;

	for (uint_32 y = 0; y < application->my_grid.size; y++)
	{
		for (uint_32 x = 0; x < application->my_grid.size; x++)
		{
			cell_coordinate_position.x = x * GRID_STEP_X + padding;
			cell_coordinate_position.y = y * GRID_STEP_Y + padding;
			cell_coordinate_position.w = GRID_STEP_X - padding;
			cell_coordinate_position.h = GRID_STEP_Y - padding;
			if (IsInRect(
				application->game_events.position.x,
				application->game_events.position.y,
				cell_coordinate_position)
				&& application->game_events.clicked
				)
			{
				SetCell(x, y, !GetCell(x, y, application->my_grid), application->my_grid);
			}
			if (GetCell(x, y, application->my_grid))
			{
				FillRect(application->surface, cell_coordinate_position, cell_color);
			}
		}
	}

	return;
}
