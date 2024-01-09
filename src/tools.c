#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "application.h"

#include "fonts.h"

#include "types.h"

static uint_32 IntToStr(char [], int);
bool IsInRect(int x, int y, SDL_Rect rect);

bool InsertIntIntoString(char * string_to_insert, uint_32 array_length, int value, const char template[])
{
    #define MAX_VALUE_SIZE 32

    char array_IntToStr_value[MAX_VALUE_SIZE];
    const int length_array_IntToStr_value = IntToStr(array_IntToStr_value, value);

    int template_length = 0;

    for (; template[template_length] != '\0'; template_length++);

    if (length_array_IntToStr_value + template_length > (int) array_length - 1)
    {
        string_to_insert[0] = 'E';
        string_to_insert[1] = 'r';
        string_to_insert[2] = 'r';
        string_to_insert[3] = 'o';
        string_to_insert[4] = 'r';
        string_to_insert[5] = '\0';
        return FALSE;
    }

    int i, j = i = 0;
    for (; template[i] != '\0'; i++, j++)
    {
        if (template[i] == '%' && template[i + 1] == 'd')
        {
            for (int k = 0; k < length_array_IntToStr_value; k++, j++)
                string_to_insert[j] = array_IntToStr_value[k];

            j = j - 1;
            i = i + 1;
        }
        else
            string_to_insert[j] = template[i];
    }
    string_to_insert[j] = '\0';

    #undef MAX_VALUE_SIZE

    return TRUE;
}
static uint_32 IntToStr(char array[], int value)
{
    if (value == 0)
    {
        array[0] = '0';
        array[1] = '\0';

        return 1;
    }

    bool _is_negative = value < 0 ? TRUE : FALSE;

    uint_8 array_length_counter = 0;
    uint_32 index = 0;

    int_8 negative = 1;

    if (_is_negative)
    {
        array[array_length_counter] = '-';
        negative = -1;
        array_length_counter = index = 1;
    }

    for (; value != 0; value /= 10, array_length_counter++)
        array[array_length_counter] = value % 10 * negative + 48;

    int return_value = array_length_counter;

    array[array_length_counter] = '\0';

    // 
    // Reversing string function
    //
    int tmp_value;
    while (index < array_length_counter - 1U)
    {
        tmp_value = array[index];
        array[index] = array[array_length_counter - 1];
        array[array_length_counter - 1] = tmp_value;

        index++;
        array_length_counter--;
    }
    //
    //

    return return_value;
}
bool RenderText(application_t * application, int x, int y, bool centered, const char * text, SDL_Color color)
{
    SDL_Surface * surface_text = TTF_RenderText_Solid(font, text, color);

    SDL_Rect position;
    if (centered)
        position = (SDL_Rect) {(x - surface_text->w) / 2, (y - surface_text->h) / 2, surface_text->w, surface_text->h};
    else
        position = (SDL_Rect) {x, y, surface_text->w, surface_text->h};

    SDL_BlitSurface(surface_text, NULL, application->surface, &position);

    SDL_FreeSurface(surface_text);

    return IsInRect(application->game_events.position.x, application->game_events.position.y, position);
}
void SetPixel(SDL_Surface * surface, int x, int y, SDL_Color pixel_color)
{
    int color = SdlColorToInt(pixel_color);
    * ((int *) surface->pixels + x + y * surface->pitch / 4) = color;

    return;
}
bool IsInRect(int x, int y, SDL_Rect rect)
{
    return (
                x >= rect.x && x < rect.x + rect.w
                &&
                y >= rect.y && y < rect.y + rect.h
           );
}
void FillRect(SDL_Surface * surface, SDL_Rect rect, SDL_Color color)
{
    for (int y = rect.y; y < rect.y + rect.h; y++)
    {
        for (int x = rect.x; x < rect.x + rect.w; x++)
        {
            SetPixel(surface, x, y, color);
        }
    }

    return;
}
int SdlColorToInt(SDL_Color color)
{
    return color.r << 16 | color.g << 8 | color.b;
}