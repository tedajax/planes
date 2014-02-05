#ifndef _PLANES_H_
#define _PLANES_H_

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.h"
#include "input.h"

#define SDL_PRINT_ERROR printf("SDL_Error: %s\n", SDL_GetError());

extern SDL_Renderer *g_renderer;
extern SDL_Window *g_window;
extern SDL_Surface *g_screen;

extern const u32 SCREEN_WIDTH;
extern const u32 SCREEN_HEIGHT;

bool window_init();
void window_destroy();

void game_update(f32 dt);
void game_render();

void app_quit();
void app_handle_event(SDL_Event _event);

#endif