#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "types.h"

typedef struct vec2_t {
	f32 x, y;
} Vec2;

Vec2 *vec2_new(f32 x, f32 y);
Vec2 *vec2_add(Vec2 *out, const Vec2 *lhs, const Vec2 *rhs);
Vec2 *vec2_sub(Vec2 *out, const Vec2 *lhs, const Vec2 *rhs);
Vec2 *vec2_mul(Vec2 *out, const Vec2 *lhs, const f32 scalar);
Vec2 *vec2_div(Vec2 *out, const Vec2 *lhs, const f32 scalar);
Vec2 *vec2_normalize(Vec2 *out, const Vec2 *vec);
Vec2 *vec2_negate(Vec2 *out, const Vec2 *vec);
f32 vec2_len(const Vec2 *vec);
f32 vec2_lenSqr(const Vec2 *vec);
f32 vec2_dist(const Vec2 *v1, const Vec2 *v2);
f32 vec2_distSqr(const Vec2 *v1, const Vec2 *v2);

#endif