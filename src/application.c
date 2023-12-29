#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "application.h"
#include "frame_loading.h"
#include "frame_menu.h"

#include "sound.h"

#include "types.h"
#include "tools.h"

extern bool _game_routine;

void FrameGameLoading(application_t * application)
{
    #define LOADING_TEXT_ARRAY_LENGTH 32

    static const char * path_to_img_load_menu = "./resources/img_load_menu.jpg";
    static bool _loaded_img_load_menu = FALSE; 
    static SDL_Surface * img_bg_loading_menu = NULL;
    
    static SDL_Color text_color = { 0x00, 0xFF, 0xFF };

    static char loading_text[LOADING_TEXT_ARRAY_LENGTH];

    if (_loaded_img_load_menu == FALSE)
    {
        img_bg_loading_menu = IMG_Load(path_to_img_load_menu);
        if (img_bg_loading_menu == NULL)
        {
            _game_routine = FALSE;
            
            return;
        }

        SDL_Thread * thread_InsertIntIntoString = SDL_CreateThread(LoadingMenuFrames, "thread_InsertIntIntoString", NULL);

        _loaded_img_load_menu = TRUE;
    }
    
    SDL_BlitSurface(img_bg_loading_menu, NULL, application->surface, NULL);

    InsertIntIntoString(loading_text, LOADING_TEXT_ARRAY_LENGTH, loaded_frames_counter * 100 / MENU_FRAMES_AMOUNT, "Loading: %d/100");

    RenderText(application->surface, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, TRUE, loading_text, text_color);

    #undef LOADING_TEXT_ARRAY_LENGTH

    return;
}
void FrameMenu(application_t * application)
{
    double const MUSIC_FINISH_MS = 15000;
    double const FADE_OUT_TIME_MS = 15000;

    static unsigned int music_start_ms = 0;

    static int frame_counter = 0;

    unsigned int current_position_ms = SDL_GetTicks() - music_start_ms;

    if (music_start_ms == 0 || current_position_ms >= MUSIC_FINISH_MS)
    {
        /*Mix_PlayMusic(music, 1);*/

        Mix_FadeInMusic(music, 1, FADE_OUT_TIME_MS);

        music_start_ms = SDL_GetTicks();
    }
    if (current_position_ms >= MUSIC_FINISH_MS - FADE_OUT_TIME_MS)
    {
        Mix_FadeOutMusic(MUSIC_FINISH_MS - current_position_ms);
    }

    SDL_BlitSurface(array_of_menu_frames[frame_counter], NULL, application->surface, NULL);

    ++frame_counter;

    if (frame_counter == MENU_FRAMES_AMOUNT)
        frame_counter ^= frame_counter;

    #undef MUSIC_FINISH

    return;
}