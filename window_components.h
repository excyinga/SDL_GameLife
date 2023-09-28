#ifndef _WINDOW_COMPONENTS_H_
#define _WINDOW_COMPONENTS_H_
#pragma once

typedef unsigned char bool;
typedef unsigned int uint_32;
typedef struct _app app_t;

struct _app
{
	SDL_Window * window;
	SDL_Surface * surface;
	TTF_Font * fonts;
};

app_t * WindowInitialization(app_t **);
void ScreenRenderingandUpdating(app_t **);
void WindowClearingandDestroying(SDL_Window **, SDL_Surface **);
void SurfaceClearing(SDL_Surface **);
void TextRendering(SDL_Surface **, SDL_Surface **, const uint_32, const uint_32);
void IntToStr_vFPS(char *, unsigned long);

#endif