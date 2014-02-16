#include "component.h"
#include "c_transform.h"
#include "c_playercontroller.h"
#include "c_spriterenderer.h"
#include "c_bulletcontroller.h"

Component *component_new(ComponentType type) {
	Component *newComp = (Component *)malloc(sizeof(Component));

	newComp->type = type;
	newComp->enabled = true;
	newComp->component = NULL;

	if (componentFuncs[type].newFunction != NULL) {
		newComp->component = componentFuncs[type].newFunction(newComp);
	}

	return newComp;
}

void component_start(Component *self) {
	if (!self->enabled) {
		return;
	}

	if (componentFuncs[self->type].startFunction != NULL) {
		componentFuncs[self->type].startFunction(self->component);
	}
}

void component_update(Component *self, f32 dt) {
	if (!self->enabled) {
		return;
	}

	if (componentFuncs[self->type].updateFunction != NULL) {
		componentFuncs[self->type].updateFunction(self->component, dt);
	}
}

void component_lateUpdate(Component *self, f32 dt) {
	if (!self->enabled) {
		return;
	}

	if (componentFuncs[self->type].lateUpdateFunction != NULL) {
		componentFuncs[self->type].lateUpdateFunction(self->component, dt);
	}
}

void component_render(Component *self) {
	if (!self->enabled) {
		return;
	}

	if (componentFuncs[self->type].renderFunction != NULL) {
		componentFuncs[self->type].renderFunction(self->component);
	}
}

ComponentFunctions componentFuncs[COMPONENT_COUNT];

void components_initialize() {
	C_REGISTER(C_TRANSFORM, transform)
	C_REGISTER(C_SPRITE_RENDERER, spriteRenderer)
	C_REGISTER(C_PLAYER_CONTROLLER, playerController)
	C_REGISTER(C_BULLET_CONTROLLER, bulletController)
}
