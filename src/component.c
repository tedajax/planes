#include "component.h"
#include "c_transform.h"
#include "c_playercontroller.h"
#include "c_spriterenderer.h"

Component *component_new(ComponentType type) {
	Component *newComponent = (Component *)malloc(sizeof(Component));

	newComponent->type = type;
	newComponent->enabled = true;
	newComponent->component = NULL;

	switch (type) {
		case C_TRANSFORM:
			newComponent->component = c_transform_new(newComponent);
			break;

		case C_SPRITE_RENDERER:
			newComponent->component = c_spriteRenderer_new(newComponent);
			break;

		case C_PLAYER_CONTROLLER:
			newComponent->component = c_playerController_new(newComponent);
			break;
	}

	return newComponent;
}

void component_start(Component *self) {
	if (!self->enabled) {
		return;
	}

	switch (self->type) {
		case C_TRANSFORM:
			c_transform_start((CTransform *)self->component);
			break;

		case C_SPRITE_RENDERER:
			c_spriteRenderer_start((CSpriteRenderer *)self->component);
			break;

		case C_PLAYER_CONTROLLER:
			c_playerController_start((CPlayerController *)self->component);
			break;
	}
}

void component_update(Component *self, f32 dt) {
	if (!self->enabled) {
		return;
	}

	switch (self->type) {
		case C_TRANSFORM:
			c_transform_update((CTransform *)self->component, dt);
			break;

		case C_SPRITE_RENDERER:
			c_spriteRenderer_update((CSpriteRenderer *)self->component, dt);
			break;

		case C_PLAYER_CONTROLLER:
			c_playerController_update((CPlayerController *)self->component, dt);
			break;
	}
}

void component_lateUpdate(Component *self, f32 dt) {
	if (!self->enabled) {
		return;
	}

	switch (self->type) {
		case C_TRANSFORM:
			c_transform_lateUpdate((CTransform *)self->component, dt);
			break;

		case C_SPRITE_RENDERER:
			c_spriteRenderer_lateUpdate((CSpriteRenderer *)self->component, dt);
			break;

		case C_PLAYER_CONTROLLER:
			c_playerController_lateUpdate((CPlayerController *)self->component,
				dt);
			break;
	}	
}

void component_render(Component *self) {
	if (!self->enabled) {
		return;
	}

	switch (self->type) {
		case C_TRANSFORM:
			c_transform_render((CTransform *)self->component);
			break;

		case C_SPRITE_RENDERER:
			c_spriteRenderer_render((CSpriteRenderer *)self->component);
			break;

		case C_PLAYER_CONTROLLER:
			c_playerController_render((CPlayerController *)self->component);
			break;
	}
}

