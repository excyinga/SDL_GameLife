#ifndef _SOUND_H_
#define _SOUND_H_
#pragma once

#include <SDL2/SDL_mixer.h>

#define SOUND_FREQUENCY		48000
#define SOUND_FORMAT		AUDIO_F32SYS
#define SOUND_CHANNELS		2
#define SOUND_CHUNKSIZE		2048

extern Mix_Music* music;

extern const char * path_to_music;

#endif 

