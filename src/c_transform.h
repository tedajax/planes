#ifndef _C_TRANSFORM_H_
#define _C_TRANSFORM_H_

#include "component.h"
#include "algebra.h"

typedef struct ctransform_t {
	Component *super;
	Vec2 *position;
	Vec2 *scale;
	f32 rotation;

	Vec2 *velocity;
	f32 angularVelocity;
} CTransform;

void *c_transform_new(Component *super);
void c_transform_start(void *pself);
void c_transform_update(void *pself, f32 dt);
void c_transform_lateUpdate(void *pself, f32 dt);
void c_transform_render(void *pself);

#endif