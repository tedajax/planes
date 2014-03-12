#include "resourcemap.h"

size_t MAX_RESOURCE_KEY_LENGTH = 64;
size_t MAX_RESOURCE_PATH_LENGTH = 256;

ResourceMap *resourceMap_new(char* filename) {
	ResourceMap *newRMap = (ResourceMap *)malloc(sizeof(ResourceMap));

	newRMap->filename = filename;
	newRMap->resources = darr_new(16);

	return newRMap;
}

void resourceMap_load(ResourceMap *self) {
	assert(self);

	FILE *inFile = fopen(self->filename, "r");

	if (!inFile) {
		printf("Error, resource map file \'%s\' not found\n", self->filename);
		return;
	}

	char keyBuffer[MAX_RESOURCE_KEY_LENGTH];
	char valueBuffer[MAX_RESOURCE_PATH_LENGTH];

	while (!feof(inFile)) {
		fscanf(inFile, "%s\n", keyBuffer);
		fscanf(inFile, "%s\n\n", valueBuffer);

		RMapNode *node = (RMapNode *)malloc(sizeof(RMapNode));
		node->key = (char *)calloc(MAX_RESOURCE_KEY_LENGTH, sizeof(char));
		node->value = (char *)calloc(MAX_RESOURCE_PATH_LENGTH, sizeof(char));

		strcpy(node->key, keyBuffer);
		strcpy(node->value, valueBuffer);

		darr_add(self->resources, node);
	}

	fclose(inFile);
}

void resourceMap_free(ResourceMap *self) {
	for (int i = 0; i < self->resources->size; ++i) {
		RMapNode *node = (RMapNode *)darr_index(self->resources, i);
		free(node->key);
		free(node->value);
		node->key = NULL;
		node->value = NULL;
		free(node);
	}
	free(self->resources);
}