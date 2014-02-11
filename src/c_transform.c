#include "components.h"

CTransform *c_transform_new(Component *super) {
	CTransform *newTx = (CTransform *)malloc(sizeof(CTransform));

	newTx->super = super;
	newTx->position = vec2_new(0, 0);
	newTx->scale = vec2_new(1, 1);
	newTx->rotation = 0;
	newTx->velocity = vec2_new(0, 0);
	newTx->angularVelocity = 0;

	return newTx;
}

void c_transform_start(CTransform *self) {

}

void c_transform_update(CTransform *self, f32 dt) {
	
}

void c_transform_lateUpdate(CTransform *self, f32 dt) {
	Vec2 timedVelocity;
	vec2_mul(&timedVelocity, self->velocity, dt);
	vec2_add(self->position, self->position, &timedVelocity);

	self->rotation += self->angularVelocity * dt;
}

void c_transform_render(CTransform *self) {

}