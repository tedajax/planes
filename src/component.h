#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <stdbool.h>

#include "sprite.h"
#include "types.h"
#include "algebra.h"

typedef enum component_type_e {
	C_TRANSFORM,
	C_SPRITE_RENDERER
} ComponentType;

struct entity_t;
void *entity_getComponent(struct entity_t *, ComponentType);

typedef struct component_t {
	ComponentType type;
	bool enabled;
	struct entity_t *entity;
	void *component;
} Component;

Component *component_new(ComponentType type);
void component_start(Component *self);
void component_update(Component *self, f32 dt);
void component_render(Component *self);

typedef struct ctransform_t {
	Component *super;
	Vec2 *position;
	Vec2 *scale;
	f32 rotation;

	Vec2 *velocity;
	f32 angularVelocity;
} CTransform;

CTransform *c_transform_new(Component *super);
void c_transform_start(CTransform *self);
void c_transform_update(CTransform *self, f32 dt);
void c_transform_render(CTransform *self);

typedef struct csprite_renderer_t {
	Component *super;
	Sprite *sprite;
} CSpriteRenderer;

CSpriteRenderer *c_spriteRenderer_new(Component *super);
void c_spriteRenderer_start(CSpriteRenderer *self);
void c_spriteRenderer_update(CSpriteRenderer *self, f32 dt);
void c_spriteRenderer_render(CSpriteRenderer *self);

#endif