#ifndef _TOOLS_H_
#define _TOOLS_H_
#pragma once

#include <SDL2/SDL.h>

#include "types.h"

bool InsertIntIntoString(char * string_to_insert, uint_32 array_length, int value, const char template[]);
void RenderText(SDL_Surface * surface, int x, int y, bool centered, const char * text, SDL_Color color);

#endif