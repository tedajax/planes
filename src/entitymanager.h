#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <glib.h>
#include <stdlib.h>

#include "types.h"

struct entity_t;

typedef enum entity_manager_add_mode_t {
	IMMEDIATE,
	QUEUED
} AddMode;

typedef struct entity_manager_t {
	u32 currentId;
	AddMode addMode;
	GPtrArray *entities;
	GQueue *addQueue;
	GQueue *removeQueue;
} EntityManager;

EntityManager *entityManager_new();
void entityManager_start(EntityManager *self);
void entityManager_update(EntityManager *self, f32 dt);
void entityManager_render(EntityManager *self);

void entityManager_add(EntityManager *self, struct entity_t *entity);
//void entityManager_get(EntityManager *self, u32 id);

#endif