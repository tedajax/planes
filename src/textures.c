#include "textures.h"
#include <SDL2/SDL.h>

HashTable *textureMap = NULL;

void textures_init() {
	assert(textureMap == NULL);

	textureMap = hashtable_new(128);
	// textureMap = g_hash_table_new_full(g_str_hash,
	// 	g_str_equal,
	// 	NULL,
	// 	texture_free);
}

void textures_destroy() {
	//todo clean up 
	// g_hash_table_unref(textureMap);
}

void textures_add(const char *name, SDL_Texture *texture) {
	assert(texture != NULL);

	hashtable_insert(textureMap, name, texture);
	// g_hash_table_insert(textureMap, (gpointer)name, texture);
}

void textures_loadRMap(ResourceMap *rmap) {
	assert(rmap);

	for (int i = 0; i < rmap->resources->size; ++i) {
		RMapNode *node = vector_index(rmap->resources, i);

		SDL_Texture *tex = texture_load(node->value);
		if (tex) {
			char *name = (char *)malloc(MAX_RESOURCE_KEY_LENGTH);
			strcpy(name, node->key);
			textures_add(name, tex);
		}
	}
}

void textures_remove(const char *name) {
	hashtable_remove(textureMap, name);
	// g_hash_table_remove(textureMap, name);
}

SDL_Texture *textures_get(const char *name) {
	return hashtable_get(textureMap, name);
	// return g_hash_table_lookup(textureMap, (gconstpointer)name);
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

void texture_free(void *texture) {
	SDL_DestroyTexture((SDL_Texture *)texture);
}