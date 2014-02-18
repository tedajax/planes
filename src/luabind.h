#ifndef _LUA_BIND_H_
#define _LUA_BIND_H_

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

typedef enum lua_bind_arg_types_e {
	LUA_ARG_BOOLEAN,
	LUA_ARG_INTEGER,
	LUA_ARG_FLOAT,
	LUA_ARG_STRING
} LuaBindArgTypes;

typedef struct lua_bind_t {
	char *funcName;
	int argc;
	LuaBindArgTypes *argt;
} LuaBind;

LuaBind *luaBind_new(const char *fname, int argc, ...);
void luaBind_call(LuaBind *self, lua_State *L, ...);
void luaBind_callv(LuaBind *self, lua_State *L, va_list argv);
void luaBind_free(void *pself);

#ifndef LUA_ERROR
	#define LUA_ERROR(L) fprintf(stderr, "Lua error in %s:%d: %s\n", \
		__FILE__, __LINE__, lua_tostring(L, -1));
#endif

#endif