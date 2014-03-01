#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "globals.h"
#include "algebra.h"
#include "components.h"
#include "dynarr.h"

typedef struct entity_t {
	i32 id;
	bool enabled;
	bool destroy;
	CTransform *transform;
	DynArr *components;
} Entity;

Entity *entity_new();
void entity_start(Entity *self);
void entity_update(Entity *self, f32 dt);
void entity_lateUpdate(Entity *self, f32 dt);
void entity_render(Entity *self);

void *entity_addComponent(Entity *self, ComponentType type);
void *entity_getComponent(Entity *self, ComponentType type);
bool entity_removeComponent(Entity *self, Component *component);

#endif