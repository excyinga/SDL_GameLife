#ifndef _TOOLS_H_
#define _TOOLS_H_
#pragma once

#include <SDL2/SDL.h>

#include "types.h"

bool InsertIntIntoString(char * string_to_insert, uint_32 array_length, int value, const char template[]);
bool RenderText(application_t * application, int x, int y, bool centered, const char * text, SDL_Color color);
void SetPixel(SDL_Surface * surface, int x, int y, SDL_Color pixel_color);
bool IsInRect(int x, int y, SDL_Rect rect);
void FillRect(SDL_Surface * surface, SDL_Rect rect, SDL_Color color);
int SdlColorToInt(SDL_Color color);

#endif