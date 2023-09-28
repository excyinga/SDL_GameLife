#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "window_components.h"

#define FRAME_DURATION 16
#define SCREEN_WIDTH   800    
#define SCREEN_HEIGHT  600

static uint_32 t_start, t_end, t_dl;

static SDL_Color fg_color = { 255, 0, 0 } /*RGB: RED*/, bg = {0xFF, 0xBF, 0x00} /*BGR : BLUE*/;

static char fps_str[27] = "FPS: ";

app_t * WindowInitialization(app_t ** app)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        return (void*) 0;
    }
    else if (TTF_Init())
    {
        printf("Couldn't initialize SDL TTF: %s\n", TTF_GetError());
        return (void*) 0;
    }
    *app = malloc(sizeof(app_t));
    (*app)->window = SDL_CreateWindow("Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if ((*app)->window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return (void*) 0;
    }
    (*app)->surface = SDL_GetWindowSurface((*app)->window);
    if ((*app)->surface == NULL)
    {
        printf("Surface could not be created! SDL_Error: %s\n", TTF_GetError());
        return (void*) 0;
    }
    (*app)->fonts = TTF_OpenFont("Sans.ttf", 24);
    if ((*app)->fonts == NULL)
    {
        printf("Fonts could not be created! SDL_Error: %s\n", TTF_GetError());
        return (void*) 0;
    }
    return (app_t*) (*app);
}
void ScreenRenderingandUpdating(app_t** app)
{
    SDL_Surface * text_surface = TTF_RenderText_Solid((*app)->fonts, "Hello, world!", fg_color);
    SDL_Surface * fps_surface = NULL;
    #define POS_CENTR_W(width) SCREEN_WIDTH / 2 - (width) / 2
    #define POS_CENTR_H(height) SCREEN_HEIGHT / 2 - (height) / 2
    uint_32 fps = 0;
    while (1)
    {
        t_start = SDL_GetTicks();
        SurfaceClearing(&(*app)->surface);
        fps_surface = TTF_RenderText_Solid((*app)->fonts, (IntToStr_vFPS(fps_str, fps), fps_str), fg_color);
        TextRendering(&fps_surface, &(*app)->surface, 0, 0);
        TextRendering(&text_surface, &(*app)->surface, POS_CENTR_W(text_surface->clip_rect.w), POS_CENTR_H(text_surface->clip_rect.h));
        SDL_UpdateWindowSurface((*app)->window);
        SDL_FreeSurface(fps_surface);
        t_dl = SDL_GetTicks();
        if (t_dl - t_start < FRAME_DURATION)
        {
            SDL_Delay(FRAME_DURATION - (t_dl - t_start));
        }
        t_end = SDL_GetTicks();
        fps = 1000 / (t_end - t_start);
    }
    #undef POS_CENTR_W(width)
    #undef  POS_CENTR_H(height)
    return;
}
void WindowClearingandDestroying(SDL_Window ** window, SDL_Surface ** surface)
{
    SDL_FreeSurface(*surface);
    SDL_DestroyWindow(*window);
    TTF_Quit();
    SDL_Quit();
}
void SurfaceClearing(SDL_Surface ** surface)
{
    for (int i = 0; i != SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j != SCREEN_WIDTH; j++)
        {
            *((int*) (*surface)->pixels + j + i * SCREEN_WIDTH) = *(int*)&bg;
        }
    }
    return;
}
void TextRendering(SDL_Surface ** src_surface, SDL_Surface ** dst_surface, const uint_32 pos_x, const uint_32 pos_y)
{
    SDL_BlitSurface(*src_surface, &(*src_surface)->clip_rect, *dst_surface, & (SDL_Rect) {pos_x, pos_y});
    return;
}
void IntToStr_vFPS(char* str, unsigned long value)
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