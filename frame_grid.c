#include "application.h"

#include "types.h"

void ClearScreen(application_t * application)
{	
	SDL_Color bg_color = {255, 255, 255};

	for (int i = 0; i < application->surface->w * application->surface->h; i++)
		((int *) application->surface->pixels)[0] = * (int *) &bg_color;

	return;
}
void GridDrawing(application_t * application, uint_16 grid_amount)
{
	SDL_Color grid_color = {0, 0, 0};

	const int GRID_STEP_X = application->surface->w / grid_amount;
	const int GRID_STEP_Y = application->surface->h / grid_amount;

	// Drawing vertical grids
	for (uint_32 y = 0; y < application->surface->h; y++)
	{
		for (uint_32 grid_counter = 0; grid_counter != grid_amount; grid_counter++)
		{
			if (grid_counter == grid_amount - 1)
				* ((int*)application->surface->pixels + grid_counter * (GRID_STEP_X) + y * application->surface->pitch / 4 - 1) = * (int *) &grid_color;
			else
				* ((int *) application->surface->pixels + grid_counter * GRID_STEP_X + y * application->surface->pitch / 4) = * (int *) &grid_color;
		}
	}

	//Drawing horizontal grids
	for (uint_32 grid_counter = 0; grid_counter != grid_amount; grid_counter++)
	{
		for (uint_32 x = 0; x < application->surface->w; x++)
		{
			if (grid_counter == grid_amount - 1)
			{
				*((int*)application->surface->pixels + x + (grid_counter * GRID_STEP_Y - 1) * application->surface->pitch / 4) = *(int*)&grid_color;
			}
			else
			{
				* ((int*)application->surface->pixels + x + grid_counter * GRID_STEP_Y * application->surface->pitch / 4) = * (int *) &grid_color;
			}
		}
	}

	return;
}