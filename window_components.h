#ifndef _WINDOW_COMPONENTS_H_
#define _WINDOW_COMPONENTS_H_
#pragma once

typedef struct _app app_t;

struct _app
{
	SDL_Window * window;
	SDL_Surface * surface;
	TTF_Font * fonts;
};

app_t * WindowInitialization();
void ScreenRenderingAndUpdating(app_t *);
void WindowClearingAndDestroying(app_t *);

#endif