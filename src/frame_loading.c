#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "application.h"
#include "frame_menu.h"

#include "fonts.h"

#include "types.h"
#include "tools.h"

#define LENGTH_OF_ARRAY_path_to_img_frames_of_menu 64 

uint_16 loaded_frames_counter = 0;

int LoadingMenuFrames(void * args)
 {
    static char path_to_img_frames_of_menu[LENGTH_OF_ARRAY_path_to_img_frames_of_menu] = "./Game Mock-up/game_frames/%d.jpg";
    static char current_frame[LENGTH_OF_ARRAY_path_to_img_frames_of_menu]; 

    for (; loaded_frames_counter < MENU_FRAMES_AMOUNT; loaded_frames_counter++)
    {
        if (InsertIntIntoString(current_frame, LENGTH_OF_ARRAY_path_to_img_frames_of_menu, loaded_frames_counter + 1, path_to_img_frames_of_menu) == FALSE)
            return FALSE;
        
        array_of_menu_frames[loaded_frames_counter] = IMG_Load((const char *) current_frame);
    }

    return TRUE;
}