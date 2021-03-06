#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <stdlib.h>

#include "types.h"
#include "vector.h"
#include "queue.h"

struct entity_t;

typedef enum entity_manager_add_mode_t {
	IMMEDIATE,
	QUEUED
} AddMode;

typedef struct entity_manager_t {
	u32 currentId;
	AddMode addMode;
	Vector *entities;
	Queue *addQueue;
	Queue *removeQueue;
} EntityManager;

EntityManager *entityManager_new();
void entityManager_start(EntityManager *self);
void entityManager_update(EntityManager *self, f32 dt);
void entityManager_render(EntityManager *self);

void entityManager_add(EntityManager *self, struct entity_t *entity);
struct entity_t *entityManager_get(EntityManager *self, i32 id);
//void entityManager_get(EntityManager *self, u32 id);
void _entityManager_addEntity(EntityManager *self, struct entity_t *entity);

void entityManager_reloadLua(EntityManager *self);

#endif