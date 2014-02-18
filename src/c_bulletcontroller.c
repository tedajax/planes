#include "components.h"
#include "entity.h"

void *c_bulletController_new(Component *super) {
	size_t bcSize = sizeof(CBulletController);
	CBulletController *self = (CBulletController *)malloc(bcSize);

	self->super = super;
	self->speed = 1000;

	return (void *)self;
}

void c_bulletController_start(void *pself) {
	C_SELF(CBulletController)

	CTransform *tx = (CTransform *)entity_getComponent(self->super->entity,
		C_TRANSFORM);

	if (tx) {
		tx->velocity->x = cosd(tx->rotation) * self->speed;
		tx->velocity->y = sind(tx->rotation) * self->speed;
	}
}

void c_bulletController_update(void *pself, f32 dt) {

}

void c_bulletController_lateUpdate(void *pself, f32 dt) {
	C_SELF(CBulletController)

	CTransform *tx = self->super->entity->transform;
	if (tx) {
		if (tx->position->x > 2000) {
			self->super->entity->destroy = true;
		}
	}
}

void c_bulletController_render(void *pself) {
}