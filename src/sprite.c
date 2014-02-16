#include "sprite.h"

Sprite *sprite_new() {
	Sprite *self = (Sprite *)malloc(sizeof(Sprite));

	self->position = vec2_new(0, 0);
	self->rotation = 0;
	self->scale = vec2_new(1, 1);
	self->width = 0;
	self->height = 0;
	self->depth = 0;
	self->origin = CENTER;
	self->flip = SDL_FLIP_NONE;
	self->texture = NULL;

	return self;
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
		SDL_Point center;
		_sprite_getOrigin(self, &center);

		SDL_Rect dst;
		_sprite_getDstRect(self, &dst);		

		SDL_RenderCopyEx(g_renderer,
			self->texture,
			NULL,
			&dst,
			self->rotation,
			&center,
			self->flip);
	}
}

SDL_Rect *_sprite_getDstRect(const Sprite *self, SDL_Rect *out) {
	assert(self);

	SDL_Point center;
	_sprite_getOrigin(self, &center);

	out->x = self->position->x - center.x * self->scale->x;
	out->y = self->position->y - center.y * self->scale->y;
	out->w = self->width * self->scale->x;
	out->h = self->height * self->scale->y;

	return out;
}

SDL_Point *_sprite_getOrigin(const Sprite *self, SDL_Point *out) {
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
