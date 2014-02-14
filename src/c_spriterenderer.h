#ifndef _C_SPRITE_RENDERER_H_
#define _C_SPRITE_RENDERER_H_

#include <SDL2/SDL.h>

#include "sprite.h"
#include "textures.h"
#include "algebra.h"

struct component_t;

typedef struct csprite_renderer_t {
	struct component_t *super;
	Sprite *sprite;
} CSpriteRenderer;

C_DECLARE(spriteRenderer)

#endif