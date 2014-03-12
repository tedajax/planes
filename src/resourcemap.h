#ifndef _RESOURCE_MAP_H_
#define _RESOURCE_MAP_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dynarr.h"

typedef struct resource_map_node_t {
	char *key;
	char *value;
} RMapNode;

typedef struct resource_map_t {
	char *filename;
	DArr *resources;
} ResourceMap;

extern size_t MAX_RESOURCE_KEY_LENGTH;
extern size_t MAX_RESOURCE_PATH_LENGTH;

ResourceMap *resourceMap_new(char* filename);
void resourceMap_load(ResourceMap *self);
void resourceMap_free(ResourceMap *self);

#endif