#pragma once
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "..\Lua\lua.h"
#include "..\Lua\lapi.h"
#include "..\Lua\lualib.h"
#include "..\Lua\lstate.h"
#include "..\Lua\lauxlib.h"
#include "..\Lua\luaconf.h"
#include "..\Lua\llimits.h"
#include "..\Lua\lapi.h"
#include "..\Lua\lfunc.h"
#include "..\Lua\lobject.h"
}


#include "../Offsets.h"


int Debug_GetRegistry(lua_State* LS) {
	r_l_pushvalue(RLS, LUA_REGISTRYINDEX);
	return 1;
}

int Debug_GetMetaTable(lua_State* LS) {
	if (lua_gettop(LS) == 0) {
		luaL_error(LS, "'debug.getrawmetatable' needs 1 argument.");
		return 0;
	}
	UnWrap(LS, RLS, 1);
	if (r_l_getmetatable(RLS, -1) == 0) {
		lua_pushnil(LS);
		return 0;
	}
	Wrap(RLS, LS, -1);
	return 1;
}

int Debug_SetMetaTable(lua_State* LS) {
	if (lua_gettop(LS) == 0) {
		luaL_error(LS, "'debug.setmetatable' needs at least 1 argument.");
		return 0;
	}
	r_l_pushboolean(RLS, r_l_setmetatable(RLS, 1));
	return 1;
}

void RegisterDebugFunctions(lua_State* LS) {
	lua_createtable(LS, 0, 0);
	{
		lua_pushcfunction(LS, Debug_GetRegistry);
		lua_setfield(LS, -2, "getregistry");

		lua_pushcfunction(LS, Debug_GetMetaTable);
		lua_setfield(LS, -2, "getmetatable");

		lua_pushcfunction(LS, Debug_SetMetaTable);
		lua_setfield(LS, -2, "setmetatable");
	}
	lua_setglobal(LS, "debug");
}