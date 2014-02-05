#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <glib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.h"
#include "planes.h"

GHashTable *textureMap;

void textures_init();
void textures_destroy();
void textures_add(const char *name, SDL_Texture *texture);
void textures_remove(const char *name);
SDL_Texture *textures_get(const char *name);

SDL_Texture *texture_load(const char *filename);
void texture_free(gpointer texture);

#endif