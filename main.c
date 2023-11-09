#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "window_components.h"

static app_t * application;

int main(int, char **) 
{
    application = WindowInitialization();
    if (!application)
        return 1;
    ScreenRenderingAndUpdating(application);
    WindowClearingAndDestroying(application);
    return 0;
}
