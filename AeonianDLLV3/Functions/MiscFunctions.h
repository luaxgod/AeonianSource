#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

#include "AeonianFunctions.h"

#include "../Lua/lua.hpp"

#include "../Authentication/base64.h"


int Base64_EncodeFunction(lua_State* LS) {
	std::string Enc = base64_encode(lua_tostring(LS, -1));
	lua_pushstring(LS, Enc.c_str());
	return 1;
}

int Base64_DecodeFunction(lua_State* LS) {
	std::string Enc = base64_decode(lua_tostring(LS, -1));
	lua_pushstring(LS, Enc.c_str());
	return 1;
}

int GetForeGWindowTitle(lua_State* LS) {
	char title[256];
	GetWindowText(GetForegroundWindow(), title, 256);
	lua_pushstring(LS, title);
	return 1;
}

/*
int GetDLLPath(lua_State* LS) {
	char path[MAX_PATH];
	GetFile("Aeonian.dll", "", path, MAX_PATH);
	lua_pushstring(LS, path);
	return 1;
}
*/

void RegisterMiscFunctions(lua_State* LS) {

	lua_register(LS, "getfgwindowtitle", GetForeGWindowTitle);
	//lua_register(LS, "getdllpath", GetDLLPath);
	//lua_register(LS, "getaeonianpath", GetDLLPath);

	lua_register(LS, "showconsole", (lua_CFunction)Aeonian_ShowConsole);
	lua_register(LS, "hideconsole", (lua_CFunction)Aeonian_HideConsole);

	lua_createtable(LS, 0, 0);
	{
		lua_pushcfunction(LS, Base64_EncodeFunction);
		lua_setfield(LS, -2, "Encode");

		lua_pushcfunction(LS, Base64_DecodeFunction);
		lua_setfield(LS, -2, "Decode");
	}
	lua_setglobal(LS, "Base64");
}
