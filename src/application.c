#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "application.h"
#include "frame_loading.h"

#include "types.h"

extern volatile bool _game_routine;

void FrameGameLoading(application_t * application)
{
    static const char * path_to_img_load_menu = "./resources/img_load_menu.jpg";
    static bool _loaded_img_load_menu = FALSE; 

    if (_loaded_img_load_menu == FALSE)
    {
        application->surface = IMG_Load(path_to_img_load_menu);
        if (application->surface == NULL)
        {
            printf("Error in \'img_load_menu\' loading\n");

            _game_routine = FALSE;
            
            return;
        }

        SDL_Thread * thread_InsertIntIntoString = SDL_CreateThread(LoadingMenuFrames, "thread_InsertIntIntoString", NULL);



        _loaded_img_load_menu = TRUE;
    }
    
    volatile static int counter = 0;




    return;
}