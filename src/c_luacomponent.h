#ifndef _C_LUA_COMPONENT_H_
#define _C_LUA_COMPONENT_H_

#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#include <lua.h>
#include <lualib.h>
#include <luajit.h>
#include <lauxlib.h>

#include <glib.h>

#include "component.h"
#include "luabind.h"

typedef struct clua_component_t {
	struct component_t *super;
	bool fileLoaded;
	char *filename;
	lua_State *L;
	GHashTable *bindTable;
} CLuaComponent;

C_DECLARE(luaComponent);

void c_luaComponent_loadFile(CLuaComponent *self, const char *filename);
void c_luaComponent_reload(CLuaComponent *self);
void c_luaComponent_call(CLuaComponent *self, const char *function, ...);
void c_luaComponent_bind(CLuaComponent *self, LuaBind *bind);

#ifndef LUA_ERROR
	#define LUA_ERROR(L) fprintf(stderr, "Lua error in %s:%d: %s\n", \
		__FILE__, __LINE__, lua_tostring(L, -1));
#endif

#endif
