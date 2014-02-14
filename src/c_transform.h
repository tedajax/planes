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

C_DECLARE(transform)

#endif