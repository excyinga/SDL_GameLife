#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "application.h"
#include "frame_loading.h"
#include "frame_menu.h"

#include "sound.h"

#include "types.h"
#include "tools.h"

void FrameGameLoading(application_t * application)
{
    #define LOADING_TEXT_ARRAY_LENGTH 32

    static const char * path_to_img_load_menu = "./resources/img_load_menu.jpg";
    static bool _loaded_img_load_menu = FALSE; 
    static SDL_Surface * img_bg_loading_menu = NULL;
    
    static SDL_Color text_color = {0x00, 0xFF, 0xFF};

    static char loading_text[LOADING_TEXT_ARRAY_LENGTH];

    if (_loaded_img_load_menu == FALSE)
    {
        img_bg_loading_menu = IMG_Load(path_to_img_load_menu);
        if (img_bg_loading_menu == NULL)
        {
            application->scene = GAME_EXITING;
            
            return;
        }

        SDL_Thread * thread_InsertIntIntoString = SDL_CreateThread(LoadingMenuFrames, "thread_InsertIntIntoString", NULL);

        _loaded_img_load_menu = TRUE;
    }
    
    if (loaded_frames_counter == MENU_FRAMES_AMOUNT)
        application->scene = GAME_MENU;

    SDL_BlitSurface(img_bg_loading_menu, NULL, application->surface, NULL);

    InsertIntIntoString(loading_text, LOADING_TEXT_ARRAY_LENGTH, loaded_frames_counter * 100 / MENU_FRAMES_AMOUNT, "Loading: %d/100");

    RenderText(application, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, TRUE, loading_text, text_color);

    #undef LOADING_TEXT_ARRAY_LENGTH

    return;
}
void FrameMenu(application_t * application)
{
    static int frame_counter = 0;

    SDL_BlitSurface(array_of_menu_frames[frame_counter], NULL, application->surface, NULL);

    ++frame_counter;

    if (frame_counter == MENU_FRAMES_AMOUNT)
        frame_counter ^= frame_counter;

    char * text_new_game = "New Game";
    static SDL_Color text_color = {0x00, 0xFF, 0xFF};

    bool choice = RenderText(application, application->surface->w, application->surface->h, TRUE, text_new_game, text_color);

    if (application->game_events.clicked && choice)
        application->scene = GAME_GRID;

    return;
}
void FrameGrid(application_t * application)
{
    GridDrawing(application, application->my_grid.size);

    return;
}
grid_data AllocGridData(int size)
{
    grid_data my_grid = {.size = size, .cells = malloc(sizeof(bool) * size * size)};
    return my_grid;
}
bool GetCell(int x, int y, grid_data data)
{
    return data.cells[y * data.size + x];
}
void SetCell(int x, int y, bool state, grid_data data)
{
    data.cells[y * data.size + x] = state;

    return;
}
