#include "textures.h"

GHashTable *textureMap = NULL;

void textures_init() {
	assert(textureMap == NULL);

	textureMap = g_hash_table_new_full(g_str_hash,
		g_str_equal,
		NULL,
		texture_free);
}

void textures_destroy() {
	g_hash_table_unref(textureMap);
}

void textures_add(const char *name, SDL_Texture *texture) {
	assert(texture != NULL);

	g_hash_table_insert(textureMap, (gpointer)name, texture);
}

void textures_remove(const char *name) {
	g_hash_table_remove(textureMap, name);
}

SDL_Texture *textures_get(const char *name) {
	return g_hash_table_lookup(textureMap, (gconstpointer)name);
}

SDL_Texture *texture_load(const char *filename) {
	SDL_Texture *newTexture = NULL;


	SDL_Surface *image = IMG_Load(filename);
	if (image == NULL) {
		printf("Unable to load image at %s\n", filename);
		return NULL;
	}

	newTexture = SDL_CreateTextureFromSurface(g_renderer, image);
	if (newTexture == NULL) {
		SDL_PRINT_ERROR
	}

	SDL_FreeSurface(image);
	return newTexture;
}

void texture_free(gpointer texture) {
	SDL_DestroyTexture((SDL_Texture *)texture);
}