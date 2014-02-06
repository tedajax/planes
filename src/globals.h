#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <SDL2/SDL.h>

#include "types.h"

#define SDL_PRINT_ERROR printf("SDL_Error: %s\n", SDL_GetError());

extern SDL_Renderer *g_renderer;
extern SDL_Window *g_window;
extern SDL_Surface *g_screen;

extern const u32 SCREEN_WIDTH;
extern const u32 SCREEN_HEIGHT;

#endif