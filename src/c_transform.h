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

CTransform *c_transform_new(Component *super);
void c_transform_start(CTransform *self);
void c_transform_update(CTransform *self, f32 dt);
void c_transform_lateUpdate(CTransform *self, f32 dt);
void c_transform_render(CTransform *self);

#endif