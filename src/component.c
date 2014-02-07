#include "component.h"

Component *component_new(ComponentType type) {
	Component *newComponent = (Component *)malloc(sizeof(Component));

	newComponent->type = type;
	newComponent->enabled = true;
	newComponent->data = NULL;

	switch (type) {
		case COMP_SPRITE_RENDERER:
			newComponent->data = c_spriteRenderer_new(newComponent);
			break;
	}

	return newComponent;
}

void component_start(Component *self) {
	if (!self->enabled) {
		return;
	}

	switch (self->type) {
		case COMP_SPRITE_RENDERER:
			c_spriteRenderer_start((CSpriteRenderer *)self->data);
			break;
	}
}

void component_update(Component *self, f32 dt) {
	if (!self->enabled) {
		return;
	}

	switch (self->type) {
		case COMP_SPRITE_RENDERER:
			c_spriteRenderer_update((CSpriteRenderer *)self->data, dt);
			break;
	}
}

void component_render(Component *self) {
	if (!self->enabled) {
		return;
	}

	switch (self->type) {
		case COMP_SPRITE_RENDERER:
			c_spriteRenderer_render((CSpriteRenderer *)self->data);
			break;
	}
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

void c_spriteRenderer_render(CSpriteRenderer *self) {
	sprite_render(self->sprite);
}
