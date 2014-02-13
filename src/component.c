#include "component.h"
#include "c_transform.h"
#include "c_playercontroller.h"
#include "c_spriterenderer.h"

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
	for (int i = 0; i < COMPONENT_COUNT; ++i) {
		componentFuncs[i].newFunction = NULL;
		componentFuncs[i].startFunction= NULL;
		componentFuncs[i].updateFunction = NULL;
		componentFuncs[i].lateUpdateFunction = NULL;
		componentFuncs[i].renderFunction = NULL;
	}

	C_REGISTER(C_TRANSFORM,
		&c_transform_new,
		&c_transform_start,
		&c_transform_update,
		&c_transform_lateUpdate,
		&c_transform_render)

	C_REGISTER(C_SPRITE_RENDERER,
		&c_spriteRenderer_new,
		&c_spriteRenderer_start,
		&c_spriteRenderer_update,
		&c_spriteRenderer_lateUpdate,
		&c_spriteRenderer_render)

	C_REGISTER(C_PLAYER_CONTROLLER,
		&c_playerController_new,
		&c_playerController_start,
		&c_playerController_update,
		&c_playerController_lateUpdate,
		&c_playerController_render)
}
