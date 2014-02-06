#include "sprite.h"

Sprite *sprite_new() {
	Sprite *newSprite = (Sprite *)malloc(sizeof(Sprite));

	newSprite->position = vec2_new(0, 0);
	newSprite->rotation = 0;
	newSprite->scale = vec2_new(1, 1);
	newSprite->width = 0;
	newSprite->height = 0;
	newSprite->origin = CENTER;
	newSprite->flip = SDL_FLIP_NONE;
	newSprite->texture = NULL;

	return newSprite;
}

void sprite_setTexture(Sprite *self, const char *textureName) {
	assert(self);

	SDL_Texture *texture = textures_get(textureName);
	if (texture) {
		self->texture = texture;

		SDL_QueryTexture(self->texture,
			NULL,
			NULL,
			&self->width,
			&self->height);
	}
}

void sprite_render(Sprite *self) {
	assert(self);

	if (self->texture) {
		SDL_Rect dst;
		sprite_getDstRect(self, &dst);

		SDL_Point center;
		sprite_getOrigin(self, &center);

		SDL_RenderCopyEx(g_renderer,
			self->texture,
			NULL,
			&dst,
			self->rotation,
			&center,
			self->flip);
	}
}

SDL_Rect *sprite_getDstRect(const Sprite *self, SDL_Rect *out) {
	assert(self);

	out->x = self->position->x;
	out->y = self->position->y;
	out->w = self->width * self->scale->x;
	out->h = self->height * self->scale->y;

	return out;
}

SDL_Point *sprite_getOrigin(const Sprite *self, SDL_Point *out) {
	assert(self);

	f32 w = sprite_getWidth(self);
	f32 h = sprite_getHeight(self);

	switch (self->origin) {
		case TOP_LEFT:
			out->x = 0;
			out->y = 0;
			break;

		case TOP:
			out->x = w / 2;
			out->y = 0;
			break;

		case TOP_RIGHT:
			out->x = w;
			out->y = 0;
			break;

		case LEFT:
			out->x = 0;
			out->y = h / 2;
			break;

		default:
		case CENTER:
			out->x = w / 2;
			out->y = h / 2;
			break;

		case RIGHT:
			out->x = w;
			out->y = h / 2;
			break;

		case BOTTOM_LEFT:
			out->x = 0;
			out->y = h;
			break;

		case BOTTOM:
			out->x = w / 2;
			out->y = h;
			break;

		case BOTTOM_RIGHT:
			out->x = w;
			out->y = h;
			break;
	}

	return out;
}

f32 sprite_getWidth(const Sprite *self) {
	assert(self);

	return self->width * self->scale->x;
}

f32 sprite_getHeight(const Sprite *self) {
	assert(self);

	return self->height * self->scale->y;
}
