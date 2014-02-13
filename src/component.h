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
	C_PLAYER_CONTROLLER,
	COMPONENT_COUNT //make sure this is always the last element in the enum
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

typedef void *(*c_new_func)(Component *);
typedef void (*c_start_func)(void *);
typedef void (*c_update_func)(void *, f32);
typedef void (*c_lateUpdate_func)(void *, f32);
typedef void (*c_render_func)(void *);

typedef struct component_functions_t {
	c_new_func newFunction;
	c_start_func startFunction;
	c_update_func updateFunction;
	c_lateUpdate_func lateUpdateFunction;
	c_render_func renderFunction;
} ComponentFunctions;

extern ComponentFunctions componentFuncs[COMPONENT_COUNT];
void components_initialize();

#define C_REGISTER(t, n, s, u, lu, r) \
	componentFuncs[t].newFunction = n; \
	componentFuncs[t].startFunction = s; \
	componentFuncs[t].updateFunction = u; \
	componentFuncs[t].lateUpdateFunction = lu; \
	componentFuncs[t].renderFunction = r;

#endif