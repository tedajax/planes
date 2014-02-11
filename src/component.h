#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <stdbool.h>
#include <stdlib.h>

#include "input.h"
#include "sprite.h"
#include "types.h"
#include "algebra.h"

typedef enum component_type_e {
	C_TRANSFORM,
	C_SPRITE_RENDERER,
	C_PLAYER_CONTROLLER
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
void component_lateUpdate(Component *self, f32 dt);
void component_render(Component *self);

#endif