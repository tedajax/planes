#include "algebra.h"

Vec2 *vec2_new(f32 x, f32 y) {
	Vec2 *new = (Vec2 *)malloc(sizeof(Vec2));
	
	new->x = x;
	new->y = y;

	return new;
}

Vec2 *vec2_add(Vec2 *out, const Vec2 *lhs, const Vec2 *rhs) {
	assert(out && lhs && rhs);

	out->x = lhs->x + rhs->x;
	out->y = lhs->y + rhs->y;

	return out;
}

Vec2 *vec2_sub(Vec2 *out, const Vec2 *lhs, const Vec2 *rhs) {
	assert(out && lhs && rhs);

	out->x = lhs->x - rhs->x;
	out->y = lhs->y - rhs->y;

	return out;
}

Vec2 *vec2_mul(Vec2 *out, const Vec2 *lhs, const f32 scalar) {
	assert(out && lhs);

	out->x = lhs->x * scalar;
	out->y = lhs->y * scalar;

	return out;
}

Vec2 *vec2_div(Vec2 *out, const Vec2 *lhs, const f32 scalar) {
	assert(out && lhs);

	out->x = lhs->x / scalar;
	out->y = lhs->y / scalar;

	return out;
}

Vec2 *vec2_normalize(Vec2 *out, const Vec2 *vec) {
	assert(out && vec);

	f32 len = vec2_len(vec);

	out->x = vec->x / len;
	out->y = vec->y / len;

	return out;
}

Vec2 *vec2_negate(Vec2 *out, const Vec2 *vec) {
	assert(out && vec);

	out->x = -vec->x;
	out->y = -vec->y;

	return out;
}

f32 vec2_len(const Vec2 *vec) {
	assert(vec);

	return sqrt(vec2_lenSqr(vec));
}

f32 vec2_lenSqr(const Vec2 *vec) {
	assert(vec);

	return pow(vec->x, 2) + pow(vec->y, 2);
}

f32 vec2_dist(const Vec2 *v1, const Vec2 *v2) {
	assert(v1 && v2);

	return sqrt(vec2_distSqr(v1, v2));
}

f32 vec2_distSqr(const Vec2 *v1, const Vec2 *v2) {
	assert(v1 && v2);

	Vec2 diff;
	vec2_sub(&diff, v1, v2);

	return vec2_lenSqr(&diff);
}

const f32 DEG_TO_RAD = 0.017453f;
const f32 RAD_TO_DEG = 57.29578f;
const f32 PI = 3.141593f;
const f32 PI_OVER_2 = 1.570796f;
const f32 TWO_PI = 6.283185f;

//const f32 PI_OVER_2 = PI / 2.0f;
//const f32 TWO_PI = PI * 2.0f;

f32 cosd(const f32 degrees) {
	return cosf(degrees * DEG_TO_RAD);
}

f32 sind(const f32 degrees) {
	return sinf(degrees * DEG_TO_RAD);
}

f32 wrapd(const f32 degrees) {
	f32 result = degrees;
	while (result > 360) { result -= 360; }
	while (result < 0) { result += 360; }
	return result;
}
