#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

#include "../Lua/lua.hpp"
#include "../ConsoleCol.h"
#include "../Obfuscation/AeonianObfuscation.h"

void Aeonian_ShowConsole(lua_State* LS) {
	::ShowWindow(GetConsoleWindow(), SW_SHOW);
}

void Aeonian_HideConsole(lua_State* LS) {
	::ShowWindow(GetConsoleWindow(), SW_HIDE);
}

static int Aeonian_SetClipboard(lua_State* LS) {
	const char* str = lua_tostring(LS, -1);
	int len = strlen(str);
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len + 1);
	void *mem_ptr = GlobalLock(hMem);
	memcpy(mem_ptr, str, len + 1);
	GlobalUnlock(hMem);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
	return 0;
}

static int Aeonian_GetClipboard(lua_State* LS) {
	if (!OpenClipboard(nullptr)) {
		lua_pushstring(LS, "");
		return 0;
	}
	auto ClipBoardText = GetClipboardData(CF_TEXT);
	lua_pushstring(LS, reinterpret_cast<char*>(ClipBoardText));
	CloseClipboard();
	return 1;
}

void AeonianPrintConsole_Red(lua_State* LS) {
	const char* ToPrint = lua_tostring(LS, -1);
	std::cout << ired << ToPrint << "\n";
}

void AeonianPrintConsole_Green(lua_State* LS) {
	const char* ToPrint = lua_tostring(LS, -1);
	std::cout << igreen << ToPrint << "\n";
}

void AeonianPrintConsole_Yellow(lua_State* LS) {
	const char* ToPrint = lua_tostring(LS, -1);
	std::cout << iyellow << ToPrint << "\n";
}

void AeonianPrintConsole_Blue(lua_State* LS) {
	const char* ToPrint = lua_tostring(LS, -1);
	std::cout << iblue << ToPrint << "\n";
}

void AeonianPrintConsole_Purple(lua_State* LS) {
	const char* ToPrint = lua_tostring(LS, -1);
	std::cout << purple << ToPrint << "\n";
}

void AeonianPrintConsole_White(lua_State* LS) {
	const char* ToPrint = lua_tostring(LS, -1);
	std::cout << white << ToPrint << "\n";
}

#define ERRMB(s, s1) MessageBox(NULL, s, s1, MB_ICONERROR | MB_OK);
#define INFOMB(s, s1) MessageBox(NULL, s, s1, MB_ICONINFORMATION | MB_OK); 

int Aeonian_ErrMessageBox(lua_State* LS) {
	ERRMB(lua_tostring(LS, -1), lua_tostring(LS, -2));
	return 1;
}

int Aeonian_InfoMessageBox(lua_State* LS) {
	INFOMB(lua_tostring(LS, -1), lua_tostring(LS, -2));
	return 1;
}

void RegisterAeonianFunctions(lua_State* LS) {
	lua_createtable(LS, 0, 0);
	{
		lua_pushcfunction(LS, (lua_CFunction)Aeonian_ShowConsole);
		lua_setfield(LS, -2, "ShowConsole");

		lua_pushcfunction(LS, (lua_CFunction)Aeonian_HideConsole);
		lua_setfield(LS, -2, "HideConsole");

		lua_pushcfunction(LS, Aeonian_SetClipboard);
		lua_setfield(LS, -2, "SetClipBoard");

		lua_pushcfunction(LS, Aeonian_GetClipboard);
		lua_setfield(LS, -2, "GetClipBoard");

		lua_pushcfunction(LS, (lua_CFunction)AeonianPrintConsole_Blue);
		lua_setfield(LS, -2, "PrintConsoleBlue");

		lua_pushcfunction(LS, (lua_CFunction)AeonianPrintConsole_Green);
		lua_setfield(LS, -2, "PrintConsoleGreen");

		lua_pushcfunction(LS, (lua_CFunction)AeonianPrintConsole_Purple);
		lua_setfield(LS, -2, "PrintConsolePurple");

		lua_pushcfunction(LS, (lua_CFunction)AeonianPrintConsole_Red);
		lua_setfield(LS, -2, "PrintConsoleRed");

		lua_pushcfunction(LS, (lua_CFunction)AeonianPrintConsole_Yellow);
		lua_setfield(LS, -2, "PrintConsoleYellow");

		lua_pushcfunction(LS, (lua_CFunction)AeonianPrintConsole_White);
		lua_setfield(LS, -2, "PrintConsoleWhite");

		lua_pushcfunction(LS, (lua_CFunction)AeonianPrintConsole_White);
		lua_setfield(LS, -2, "PrintConsole");

		lua_pushcfunction(LS, Aeonian_InfoMessageBox);
		lua_setfield(LS, -2, "InfoMessageBox");

		lua_pushcfunction(LS, Aeonian_ErrMessageBox);
		lua_setfield(LS, -2, "ErrorMessageBox");

		lua_pushcfunction(LS, (lua_CFunction)Aeonian_Obfuscate);
		lua_setfield(LS, -2, "Obfuscate");
	}
	lua_setglobal(LS, "Aeonian");
}