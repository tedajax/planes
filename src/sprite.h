#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.h"
#include "textures.h"
#include "algebra.h"
#include "globals.h"

typedef enum origins_e {
	TOP_LEFT,
	TOP,
	TOP_RIGHT,
	LEFT,
	CENTER,
	RIGHT,
	BOTTOM_LEFT,
	BOTTOM,
	BOTTOM_RIGHT
} Origins;

typedef struct sprite_t {
	Vec2 *position;
	Vec2 *scale;
	f32 rotation;
	i32 width;
	i32 height;
	i32 depth;
	Origins origin;
	SDL_RendererFlip flip;

	SDL_Texture *texture;
} Sprite;

Sprite *sprite_new();
void sprite_setTexture(Sprite *self, const char *textureName);
void sprite_render(Sprite *self);
SDL_Rect *_sprite_getDstRect(const Sprite *self, SDL_Rect *out);
SDL_Point *_sprite_getOrigin(const Sprite *self, SDL_Point *out);
f32 sprite_getWidth(const Sprite *self);
f32 sprite_getHeight(const Sprite *self);

#endif