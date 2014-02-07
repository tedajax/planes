#ifndef _PLANES_H_
#define _PLANES_H_

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.h"
#include "input.h"
#include "textures.h"
#include "sprite.h"
#include "entity.h"
#include "component.h"

#include "globals.h"

bool window_init();
void window_destroy();

void game_update(f32 dt);
void game_render();

void app_quit();
void app_handle_event(SDL_Event _event);

#endif