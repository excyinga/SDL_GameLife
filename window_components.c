#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "window_components.h"

#define TRUE            1
#define FALSE           0
#define SCREEN_WIDTH    800    
#define SCREEN_HEIGHT   600
#define FPS_VALUE_ARRAY_SIZE 29
#define FRAME_DURATION  16

typedef char unsigned uint_8;
typedef int unsigned uint_32;
typedef long long unsigned uint_64;
typedef enum _position_flags position_flags;
typedef struct _position position;

enum _position_flags
{
    NO_FLAGS = 0,
    CENTERED = 1
};

struct _position
{
    position_flags flag;
    struct
    {
        int x, y;
    };
};

static char text_fps[FPS_VALUE_ARRAY_SIZE] = "FPS: ";

void SurfaceClearing(SDL_Surface *, SDL_Color const *);
void TextRendering(app_t *, position *, SDL_Color, const char*);
char const * IntToStr_vFPS(char *, uint_32);

app_t * WindowInitialization()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        return (void*) 0;
    }
    else if (TTF_Init())
    {
        printf("Couldn't initialize SDL TTF: %s\n", TTF_GetError());
        return (void*) 0;
    }
    app_t * app = malloc(sizeof(app_t));
    app->window = SDL_CreateWindow("Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (app->window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return (void*) 0;
    }
    app->surface = SDL_GetWindowSurface(app->window);
    if (app->surface == NULL)
    {
        printf("Surface could not be created! SDL_Error: %s\n", TTF_GetError());
        return (void*) 0;
    }
    app->fonts = TTF_OpenFont("Sans.ttf", 24);
    if (app->fonts == NULL)
    {
        printf("Fonts could not be created! SDL_Error: %s\n", TTF_GetError());
        return (void*) 0;
    }
    return (app_t *) app;
}
void ScreenRenderingAndUpdating(app_t * app)
{
    void DrawingGrid(unsigned, SDL_Surface *);
    uint_32 t_start, t_end, t_dl, fps = 0;;
    SDL_Color bg = {255, 255, 255}, fg = {0, 0, 0};
    uint_8 non_exit = 1;
    SDL_Event event;
    while (non_exit)
    {
        t_start = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                non_exit = 0;
                break;
            }
        }
        SurfaceClearing(app->surface, &bg);
        DrawingGrid(10, app->surface);
        TextRendering(app, &(position) {.x = 0, 0}, fg, IntToStr_vFPS(text_fps, fps));
        SDL_UpdateWindowSurface(app->window);
        t_dl = SDL_GetTicks();
        if (t_dl - t_start < FRAME_DURATION)
        {
            SDL_Delay(FRAME_DURATION - (t_dl - t_start));
        }
        t_end = SDL_GetTicks();
        fps = 1000 / (t_end - t_start);
    }
    return;
}
void WindowClearingAndDestroying(app_t * app)
{
    TTF_CloseFont(app->fonts);
    SDL_FreeSurface(app->surface);
    SDL_DestroyWindow(app->window);
    TTF_Quit();
    SDL_Quit();
    free(app);
    return;
}
void SurfaceClearing(SDL_Surface * surface, SDL_Color const * color_bg)
{
    for (int i = 0; i != SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j != SCREEN_WIDTH; j++)
        {
            SetPixel(surface, j, i, color_bg->a << 24 | color_bg->r << 16 | color_bg->g << 8 | color_bg->b);
        }
    }
    return;
}
void TextRendering(app_t * app, position * pos, SDL_Color text_color, const char * text)
{
    SDL_Surface * text_surface; 
    text_surface = TTF_RenderText_Solid(app->fonts, text, text_color);
    if (pos->flag == CENTERED)
    {
        #define POS_CENTR_W(width) SCREEN_WIDTH / 2 - (width) / 2
        #define POS_CENTR_H(height) SCREEN_HEIGHT / 2 - (height) / 2 
        pos->x = POS_CENTR_W(text_surface->clip_rect.w);
        pos->y = POS_CENTR_H(text_surface->clip_rect.h);
        #undef POS_CENTR_W
        #undef POS_CENTR_H
    }
    SDL_BlitSurface(text_surface, &text_surface->clip_rect, app->surface, &(SDL_Rect) {pos->x, pos->y});
    SDL_FreeSurface(text_surface);
    return;
}
char const * IntToStr_vFPS(char * str_value, uint_32 value) 
{
    #define START_POS 5
    uint_8 i = START_POS;
    for (; value != 0; i++, value /= 10)
    {
        str_value[i] = value % 10 + 48;
    }
    str_value[i] = '\0';
    uint_32 tmp;
    for (int j = START_POS; i - 1 > j; i--, j++)
    {
        tmp = str_value[j];
        str_value[j] = str_value[i - 1];
        str_value[i - 1] = tmp;
    }
    #undef START_POS
    return str_value;
}
void DrawingGrid(unsigned grid_number, SDL_Surface * surface)
{
    void SetPixel(SDL_Surface *, int, int, int);
    #define STEP_W SCREEN_WIDTH / grid_number
    #define STEP_H SCREEN_HEIGHT / grid_number
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (unsigned int pix = 0; pix <= grid_number; pix++)
        {
            if (pix == grid_number)
            {
                SetPixel(surface, pix * STEP_W - 1, i, 0);
            }
            else
            {
                SetPixel(surface, pix * STEP_W, i, 0);
            }
        }
    }
    for (unsigned int i = 0; i <= grid_number; i++)
    {
        for (unsigned int pix = 0; pix < SCREEN_WIDTH; pix++)
        {
            if (i == grid_number)
            {
                SetPixel(surface, pix, i * STEP_H - 1, 0);
            }
            else
            {
                SetPixel(surface, pix, i * STEP_H, 0);
            }   
        }       
    }
    return;
}
void SetPixel(SDL_Surface * surface, int x, int y, int color)
{   
    ((int *) surface->pixels)[x + y * surface->w] = color;
    return;
}
