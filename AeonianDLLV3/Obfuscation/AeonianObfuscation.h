#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

#include "SecureScriptCrypter.h"

#include "../Lua/lua.h"

#define ERRORMSGBOX(body, title) MessageBox(NULL, body, title, MB_ICONERROR | MB_OK);
#define INFOMSGBOX(body, title) MessageBox(NULL, body, title, MB_ICONINFORMATION | MB_OK);

void Aeonian_Obfuscate(lua_State* LS) {
	std::string ScriptToSecure = lua_tostring(LS, -1);

	for (std::string::size_type i = 0; i < ScriptToSecure.size(); ++i) {

	}

	ERRORMSGBOX("This Function Is Not In Aeonian Yet!", "Error While Obfuscating!");
}