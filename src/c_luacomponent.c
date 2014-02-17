#include "components.h"
#include "entity.h"

void *c_luaComponent_new(Component *super) {
	size_t lcSize = sizeof(CLuaComponent);
	CLuaComponent *self = (CLuaComponent * )malloc(lcSize);

	self->super = super;
	self->fileLoaded = false;
	self->filename = NULL;
	self->L = lua_open();
	luaL_openlibs(self->L);

	return (void *)self;
}

void c_luaComponent_start(void *pself) {
	C_SELF(CLuaComponent)

	if (!self->fileLoaded) {
		return;
	}

	lua_getglobal(self->L, "start");
	if (lua_pcall(self->L, 0, 0, 0) != 0) {
		LUA_ERROR(self->L)
	}
}

void c_luaComponent_update(void *pself, f32 dt) {
	C_SELF(CLuaComponent)

	if (!self->fileLoaded) {
		return;
	}	

	lua_getglobal(self->L, "update");
	lua_pushnumber(self->L, dt);
	if (lua_pcall(self->L, 1, 0, 0) != 0) {
		LUA_ERROR(self->L)
	}
}

void c_luaComponent_lateUpdate(void *pself, f32 dt) {
	C_SELF(CLuaComponent)

	if (!self->fileLoaded) {
		return;
	}

	lua_getglobal(self->L, "lateUpdate");
	lua_pushnumber(self->L, dt);
	if (lua_pcall(self->L, 1, 0, 0) != 0) {
		LUA_ERROR(self->L)
	}
}

void c_luaComponent_render(void *pself) {
	C_SELF(CLuaComponent)

	if (!self->fileLoaded) {
		return;
	}

	lua_getglobal(self->L, "render");
	if (lua_pcall(self->L, 0, 0, 0) != 0) {
		LUA_ERROR(self->L)
	}
}

void c_luaComponent_loadFile(CLuaComponent *self, const char *filename) {
	self->filename = (char *)realloc(self->filename, strlen(filename));
	strcpy(self->filename, filename);
	luaL_dofile(self->L, filename);
	self->fileLoaded = true;
}