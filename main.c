#include <stdio.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "window_components.h"

app_t * application;

int main() 
{
    if (!(application = WindowInitialization()))
        return 1;
    ScreenRenderingAndUpdating(application);
    WindowClearingAndDestroying(application);
    return 0;
}
