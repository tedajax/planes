#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <stdbool.h>

#include "sprite.h"
#include "types.h"

typedef enum component_type_e {
	COMP_TRANSFORM,
	COMP_SPRITE_RENDERER
} ComponentType;

typedef struct component_t {
	ComponentType type;
	bool enabled;
	void *data;
} Component;

Component *component_new(ComponentType type);
void component_start(Component *self);
void component_update(Component *self, f32 dt);
void component_render(Component *self);

typedef struct csprite_renderer_t {
	Component *super;
	Sprite *sprite;
} CSpriteRenderer;

CSpriteRenderer *c_spriteRenderer_new(Component *super);
void c_spriteRenderer_start(CSpriteRenderer *self);
void c_spriteRenderer_update(CSpriteRenderer *self, f32 dt);
void c_spriteRenderer_render(CSpriteRenderer *self);

#endif