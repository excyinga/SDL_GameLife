#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <stdio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define SCREEN_WIDTH   800    
#define SCREEN_HEIGHT  600

#define FRAME_DURATION 16

typedef unsigned char bool;

static SDL_Window * window = NULL;
static SDL_Renderer * renderer = NULL;
static SDL_Surface * surface = NULL;
static SDL_Texture * texture = NULL;
static TTF_Font * fonts = NULL; 

unsigned int t_start, t_end, t_dl;

SDL_Color fg_color = { 255, 0, 0 };

char fps_str[27] = "FPS: ";

bool InitializationComponents();
bool ScreenRendering();
void ScreenUpdating();
void ScreenClean();

void int_to_str(char *, unsigned long);

int main() 
{
    if (!InitializationComponents())
        return 1;
    ScreenRendering();
    return 0;
}

bool InitializationComponents()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		return 0;
	}
    if (TTF_Init() != 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", TTF_GetError());
        return 0;
    }
    return 1;
}
bool ScreenRendering()
{    
    window = SDL_CreateWindow("Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    surface = SDL_GetWindowSurface(window);
    if (surface == NULL)
    {
        printf("Surface could not be created! SDL_Error: %s\n", TTF_GetError());
        return;
    }
    fonts = TTF_OpenFont("Sans.ttf", 24);
    if (fonts == NULL )
    {
        printf("Fonts could not be created! SDL_Error: %s\n", TTF_GetError());
        return;
    }    
    /* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL ) 
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    } */

    TTF_Font * fps_fonts = TTF_OpenFont("Sans.ttf", 10); 

    SDL_Surface * text_surface = TTF_RenderText_Solid(fonts, "Hello, world!", fg_color);
    SDL_Surface * fps_surface = NULL;
    SDL_Rect    fps_rect_surface,
                text_rect_surface = {0, 0, text_surface -> w, text_surface -> h},
                displaying_text_rect_surface = {SCREEN_WIDTH / 2 - text_surface -> w / 2, SCREEN_HEIGHT / 2 - text_surface -> h / 2, 0, 0},
                displaying_fps_rect_surface = {0, 0, 0, 0};

    unsigned int fps = 0;

    while (1)
    {
        t_start = SDL_GetTicks();
        for (int i = 0; i != SCREEN_HEIGHT; i++)
        {
            for (int j = 0; j != SCREEN_WIDTH; j++)
            {
                *((int*)surface->pixels + j + i * SCREEN_WIDTH) = 0xFFFF00;
            }
        }
        SDL_BlitSurface(text_surface, &text_rect_surface, surface, &displaying_text_rect_surface);
        fps_surface = TTF_RenderText_Solid(fonts, (int_to_str(fps_str, fps), fps_str), fg_color);
        fps_rect_surface = (SDL_Rect) {0, 0, fps_surface -> w, fps_surface -> h};
        SDL_BlitSurface(fps_surface, &fps_rect_surface, surface, &displaying_fps_rect_surface);
        SDL_UpdateWindowSurface(window);
        SDL_FreeSurface(fps_surface);
        t_dl = SDL_GetTicks();
        if (t_dl - t_start < FRAME_DURATION)
        {
            SDL_Delay(FRAME_DURATION - (t_dl - t_start));
        }
        t_end = SDL_GetTicks();
        fps = 1000 / (t_end - t_start);
    }

    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 1;
}
void int_to_str(char * str, unsigned long value)
{  
    #define START_POS 5
    int i;
    for (i = START_POS; value != 0; i++, value /= 10)
    {
        str[i] = value % 10 + 48;
    }
    str[i] = '\0';
    unsigned long long tmp;
    for (int j = START_POS; i - 1 > j; i--, j++)
    {
        tmp = str[j];
        str[j] = str[i - 1];
        str[i - 1] = tmp;
    }
    #undef START_POS
    return;
}