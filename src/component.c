#include "component.h"

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

CSpriteRenderer *c_spriteRenderer_new(Component *super) {
	CSpriteRenderer *newSR = (CSpriteRenderer *)malloc(sizeof(CSpriteRenderer));

	newSR->super = super;
	newSR->sprite = sprite_new();

	return newSR;
}

void c_spriteRenderer_start(CSpriteRenderer *self) {

}

void c_spriteRenderer_update(CSpriteRenderer *self, f32 dt) {

}

void c_spriteRenderer_lateUpdate(CSpriteRenderer *self, f32 dt) {

}

void c_spriteRenderer_render(CSpriteRenderer *self) {
	CTransform *tx = (CTransform *)entity_getComponent(self->super->entity,
		C_TRANSFORM);

	if (tx) {
		self->sprite->position->x = tx->position->x;
		self->sprite->position->y = tx->position->y;
		self->sprite->rotation = tx->rotation;
	}

	sprite_render(self->sprite);
}

CPlayerController *c_playerController_new(Component *super) {
	size_t pcSize = sizeof(CPlayerController);
	CPlayerController *newPC = (CPlayerController *)malloc(pcSize);

	newPC->super = super;
	newPC->speed = 500;

	return newPC;
}

void c_playerController_start(CPlayerController *self) {

}

void c_playerController_update(CPlayerController *self, f32 dt) {
	CTransform *tx = (CTransform *)entity_getComponent(self->super->entity,
		C_TRANSFORM);

	i32 rlDirection = 0;
	i32 udDirection = 0;

	if (input_key(SDL_SCANCODE_LEFT)) {
		--rlDirection;
	}
	if (input_key(SDL_SCANCODE_RIGHT)) {
		++rlDirection;
	}

	if (input_key(SDL_SCANCODE_UP)) {
		--udDirection;
	}
	if (input_key(SDL_SCANCODE_DOWN)) {
		++udDirection;
	}

	if (tx) {
		tx->velocity->x = rlDirection * self->speed;
		tx->velocity->y = udDirection * self->speed;
	}
}

void c_playerController_lateUpdate(CPlayerController *self, f32 dt) {

}

void c_playerController_render(CPlayerController *self) {

}