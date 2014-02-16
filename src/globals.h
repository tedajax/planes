#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "types.h"
#include "entitymanager.h"

#define SDL_PRINT_ERROR printf("SDL_Error: %s\n", SDL_GetError());
#define STUBBED(x) do { \
	static bool seenIt = false; \
	if (!seenIt) { \
		seenIt = true; \
		fprintf(stderr, "STUBBED: %s at %s (%s:%d)\n", \
			x, __FUNCTION__, __FILE__, __LINE__); \
	} \
} while (0);

extern SDL_Renderer *g_renderer;
extern SDL_Window *g_window;
extern SDL_Surface *g_screen;
extern EntityManager *g_entities;

extern const u32 SCREEN_WIDTH;
extern const u32 SCREEN_HEIGHT;

#endif