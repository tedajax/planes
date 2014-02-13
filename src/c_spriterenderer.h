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

void *c_spriteRenderer_new(struct component_t *super);
void c_spriteRenderer_start(void *pself);
void c_spriteRenderer_update(void *pself, f32 dt);
void c_spriteRenderer_lateUpdate(void *pself, f32 dt);
void c_spriteRenderer_render(void *pself);


#endif