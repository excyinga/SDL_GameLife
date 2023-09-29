#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "window_components.h"

#define TRUE            1
#define FALSE           0
#define FRAME_DURATION  16
#define SCREEN_WIDTH    800    
#define SCREEN_HEIGHT   600

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

void SurfaceClearing(SDL_Surface *, SDL_Color const *);
void TextRendering(app_t *, position *, SDL_Color, const char*);
char const * IntToStr(uint_32);
char const* MergeStrings(char const *, char const *);

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
    SDL_Event* event = malloc(sizeof(SDL_Event));
    while (TRUE)
    {
        t_start = SDL_GetTicks();
        SDL_PollEvent(event);
        if (event->type == SDL_QUIT)
        {
            break;
        }
        SurfaceClearing(app->surface, &bg);
        TextRendering(app, &(position) {.x = 0, 0}, fg, MergeStrings("FPS: ", IntToStr(fps)));
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
            *((int*) surface->pixels + j + i * SCREEN_WIDTH) = *(int*) &*color_bg;
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
        #undef POS_CENTR_W(width)
        #undef POS_CENTR_H(height)
    }
    SDL_BlitSurface(text_surface, &text_surface->clip_rect, app->surface, &(SDL_Rect) {pos->x, pos->y});
    SDL_FreeSurface(text_surface);
    return;
}
char const * IntToStr(uint_32 value) 
{
    uint_8 i = 0;
    static char* str_value = NULL;
    if (str_value)
    {
        free(str_value);
        str_value = NULL;
    }
    str_value = malloc(sizeof(char) * 22);
    for (; value != 0; i++, value /= 10)
    {
        str_value[i] = value % 10 + 48;
    }
    str_value[i] = '\0';
    uint_32 tmp;
    for (int j = 0; i - 1 > j; i--, j++)
    {
        tmp = str_value[j];
        str_value[j] = str_value[i - 1];
        str_value[i - 1] = tmp;
    }
    return str_value;
}
char const* MergeStrings(char const* str1, char const* str2)
{
    uint_32 str_len1 = 0;
    uint_32 str_len2 = 0;
    for (; str1[str_len1] != '\0'; str_len1++) {}
    for (; str2[str_len2] != '\0'; str_len2++) {}
    static char* merged_str = NULL;
    if (merged_str)
    {
        free(merged_str);
        merged_str = NULL;
    }
    uint_64 merged_str_len = str_len1 + str_len2 + 1;
    merged_str = malloc(sizeof(char) * merged_str_len);
    int i = 0;
    for (; i < str_len1; i++) { merged_str[i] = str1[i]; }
    for (; i < merged_str_len - 1; i++) { merged_str[i] = str2[i - str_len1]; }
    merged_str[i] = '\0';
    return merged_str;
}