#include <stdio.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "window_components.h"

static app_t* app;

int main() 
{
    if (!(app = WindowInitialization(&app)))
        return 1;
    ScreenRenderingandUpdating(&app), WindowClearingandDestroying(&app->window, &app->surface);
    free(app);
    return 0;
}
