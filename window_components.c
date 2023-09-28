#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "window_components.h"

#define TRUE            1
#define FALSE           0
#define FRAME_DURATION  16
#define SCREEN_WIDTH    800    
#define SCREEN_HEIGHT   600

typedef unsigned int uint_32;
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

extern app_t* application;

void SurfaceClearing(SDL_Surface*, SDL_Color const *);
void TextRendering(app_t *, position *, SDL_Color, const char*);
//char const * IntToStr_vFPS(unsigned long long);

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
    uint_32 t_start, t_end, t_dl;
    SDL_Color fg = { 255, 0, 0 } /*RGB: RED*/, bg = { 0xFF, 0xBF, 0x00 }; /*BGR : BLUE*/
    uint_32 fps = 0;
    #define ToStr(x) #x
    while (TRUE)
    {
        t_start = SDL_GetTicks();
        SurfaceClearing(app->surface, &bg);
        TextRendering(app, &(position) {.x = 0, 0}, fg, "FPS: "ToStr(fps));
        TextRendering(app, &(position) {CENTERED}, fg, "Hello, world!");
        SDL_UpdateWindowSurface(app->window);
        t_dl = SDL_GetTicks();
        if (t_dl - t_start < FRAME_DURATION)
        {
            SDL_Delay(FRAME_DURATION - (t_dl - t_start));
        }
        t_end = SDL_GetTicks();
        fps = 1000 / (t_end - t_start);
    }
    #undef ToStr(x)
    return;
}
void WindowClearingAndDestroying(app_t * app)
{
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
            *((int*) surface->pixels + j + i * SCREEN_WIDTH) = *(int*) &color_bg;
        }
    }
    return;
}
void TextRendering(app_t * app, position * pos, SDL_Color text_color, const char * text)
{
    #define POS_CENTR_W(width) SCREEN_WIDTH / 2 - (width) / 2
    #define POS_CENTR_H(height) SCREEN_HEIGHT / 2 - (height) / 2 
    SDL_Surface * text_surface; 
    text_surface = TTF_RenderText_Solid(application->fonts, text, text_color);
    if (pos->flag == CENTERED)
    {
        pos->x = POS_CENTR_W(text_surface->clip_rect.w);
        pos->y = POS_CENTR_H(text_surface->clip_rect.h);
    }
    SDL_BlitSurface(text_surface, &text_surface->clip_rect, app->surface, &(SDL_Rect) {pos->x, pos->y});
    SDL_FreeSurface(text_surface);
    #undef POS_CENTR_W(width)
    #undef POS_CENTR_H(height)
    return;
}
/* char const* IntToStr_vFPS(unsigned long long value)
{
    int i = 0;
    static char text[21];
    for (; value != 0; i++, value /= 10)
    {
        text[i] = value % 10 + 48;
    }
    text[i] = '\0';
    unsigned long long tmp;
    for (int j = 0; i - 1 > j; i--, j++)
    {
        tmp = text[j];
        text[j] = text[i - 1];
        text[i - 1] = tmp;
    }
    return text;
} */