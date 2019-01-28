#include <Windows.h>
#include <string>
#include <iostream>
#include <Psapi.h>

#include "ConsoleCol.h"
#include "Authentication.h"
#include "Memory.h"
#include "Offsets.h"
#include "LuaWrapper.h"
#include "Bypasses.h"
#include "Functions/FunctionIncludes.h"
#include "Commands/Commands.h"


void WrapGlobal(DWORD rL, lua_State* L, const char* s)
{
	r_l_getglobal(rL, s);
	Wrap(rL, L, -1);
	lua_setglobal(L, s);
	r_l_pop(rL, 1);
}

DWORD WINAPI aeopipe(PVOID lvpParameter)
{
	string WholeScript = "";
	HANDLE hPipe;
	char buffer[999999];
	DWORD dwRead;
	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\ReadMeYouGay"),
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_WAIT,
		1,
		999999,
		999999,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	while (hPipe != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)
		{
			while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
			{
				buffer[dwRead] = '\0';
				try {
					try {
						WholeScript = WholeScript + buffer;
					}
					catch (...) {
					}
				}
				catch (std::exception e) {

				}
				catch (...) {

				}
			}
			Wrapper::Execute_Script(WholeScript);
			WholeScript = "";
		}
		DisconnectNamedPipe(hPipe);
	}
}


DWORD WINAPI aeocmdpipe(PVOID lvpParameter)
{
	string WholeScript = "";
	HANDLE hPipe;
	char buffer[999999];
	DWORD dwRead;
	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\ReadMeYouMegaGay"),
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_WAIT,
		1,
		999999,
		999999,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	while (hPipe != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)
		{
			while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
			{
				buffer[dwRead] = '\0';
				try {
					try {
						WholeScript = WholeScript + buffer;
					}
					catch (...) {
					}
				}
				catch (std::exception e) {

				}
				catch (...) {

				}
			}
			//Execute_Script(WholeScript);
			WholeScript = "";
		}
		DisconnectNamedPipe(hPipe);
	}
}

void ConsoleBypass(const char* Title) {
	DWORD superskiddoisachink;
	VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &superskiddoisachink);
	*(BYTE*)(&FreeConsole) = 0xC3;
	AllocConsole();
	SetConsoleTitleA(Title);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConsoleHandle = GetConsoleWindow();
	::SetWindowPos(ConsoleHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::ShowWindow(ConsoleHandle, SW_NORMAL);
}

#define seti(rL, i) DWORD* identity  = (DWORD*)(rL - 32); *identity ^= (i ^ (unsigned __int8)*identity) & 0x1F;

std::string Input() {
	std::string i;
	std::getline(std::cin, i);
	return i;
}



void GetFile(const char* dllName, const char* fileName, char* buffer, int bfSize) {
	GetModuleFileName(GetModuleHandle(dllName), buffer, bfSize);
	if (strlen(fileName) + strlen(buffer) < MAX_PATH) {
		char* pathEnd = strrchr(buffer, '\\');
		strcpy(pathEnd + 1, fileName);
	}
	else {
		*buffer = 0;
	}
}


int ReadFile(const std::string& path, std::string& out, unsigned char binary) {
	std::ios::openmode mode = std::ios::in;
	if (binary)
		mode |= std::ios::binary;

	std::ifstream file(path, mode);
	if (file.is_open()) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		out = buffer.str();
		file.close();
		return 1;
	}

	file.close();
	return 0;
}

std::string initbuffer;

void readauthstuff() {
	char cPath[MAX_PATH];
	GetFile("Aeonian.dll", "Auth\\", cPath, MAX_PATH);
	std::string aePath = cPath;
	std::string iPath = aePath + "Auth.bin";
	ReadFile(iPath, initbuffer, 0);
}



void maininit() {
	ConsoleBypass("Aeonian | Level 6 Debug Console");
	std::cout << iblue << "Welcome To Aeonian!\n";
	CommandSettings::Core::Initialized = false;
	/*
	XorS(AUTHMSG, "Authenticating... ");
	std::cout << iyellow << AUTHMSG.decrypt();
	readauthstuff();
	std::vector<string> AuthInfo = split_string(initbuffer, '|');
	std::string username = base64_decode(AuthInfo.at(0));
	std::string password = base64_decode(AuthInfo.at(1));
	AuthenticateCredentials(username, password, AuthLevel::InformationUpdate);

	if (!isauthed)
	{
		exit(0);
	}

	if (firsttime)
	{
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
		INFOMB("This seems to be your first time using Aeonian!", "Welcome!");
		INFOMB("This tutorial will not take long!", "Welcome!");
		INFOMB("To run a script press execute in the UI", "Welcome!");
		INFOMB("To run a command type the desired command with the desired args in the console (E.G clicktp)(or ff me) Remember to type 'cmds' for a list!", "Welcome!");
		INFOMB("That concludes the Aeonian tutorial, have fun!", "Welcome!");
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	}

	*/
	std::cout << iyellow << "Scanning... ";
	ScriptContext = Memory::Scan((BYTE*)&ScriptContextVFT_Addy, (BYTE*)"xxxx", PAGE_READWRITE);
	if (!ScriptContext) {
		std::cout << ired << "ScriptContext Scan Failed!\n";
		system("pause");
		exit(0);
	}
	std::cout << igreen << "Success!\n";

	std::cout << iyellow << "Setting Lua States... ";
	int v39 = ScriptContext;
	int v51 = 0;
	RLS = *(DWORD *)(v39 + 56 * v51 + 164) - (v39 + 56 * v51 + 164);
	if (!RLS) {
		std::cout << ired << "Failed to set roblox lua state!\n";
		system("pause");
	}

	LS = luaL_newstate();
	if (!LS)
	{
		std::cout << ired << "Failed to init vanilla lua state!\n";
		system("pause");
	}
	luaL_openlibs(LS);

	std::cout << igreen << "Success!\n";

	std::cout << iyellow << "Setting Level 6 Identity... ";
	seti(RLS, 6);
	std::cout << igreen << "Success!\n";


	std::cout << iyellow << "Setting Up Environment... ";
	EnableInt3BPHandler();
	RegisterCustomFunctions(LS); //All The H0T Functions In Aeonian!

	lua_newtable(LS);
	lua_pushcfunction(LS, GlobalsIndex);
	lua_setfield(LS, -2, "__index");
	lua_pushstring(LS, "The metatable is locked");
	lua_setfield(LS, -2, "__metatable");
	lua_setmetatable(LS, LUA_GLOBALSINDEX);

	WrapGlobal(RLS, LS, "game");
	WrapGlobal(RLS, LS, "Game");
	WrapGlobal(RLS, LS, "workspace");
	WrapGlobal(RLS, LS, "Workspace");
	WrapGlobal(RLS, LS, "Instance");
	WrapGlobal(RLS, LS, "math");
	WrapGlobal(RLS, LS, "warn");
	WrapGlobal(RLS, LS, "shared");
	WrapGlobal(RLS, LS, "Wait");
	WrapGlobal(RLS, LS, "wait");
	WrapGlobal(RLS, LS, "delay");
	WrapGlobal(RLS, LS, "Delay");
	WrapGlobal(RLS, LS, "tick");
	WrapGlobal(RLS, LS, "LoadLibrary");
	WrapGlobal(RLS, LS, "Axes");
	WrapGlobal(RLS, LS, "BrickColor");
	WrapGlobal(RLS, LS, "CFrame");
	WrapGlobal(RLS, LS, "typeof");
	WrapGlobal(RLS, LS, "type");
	WrapGlobal(RLS, LS, "spawn");
	WrapGlobal(RLS, LS, "Spawn");
	WrapGlobal(RLS, LS, "print");
	WrapGlobal(RLS, LS, "printidentity");
	WrapGlobal(RLS, LS, "ypcall");
	WrapGlobal(RLS, LS, "Vector2int16");
	WrapGlobal(RLS, LS, "elapsedTime");
	WrapGlobal(RLS, LS, "version");
	WrapGlobal(RLS, LS, "PluginManager");
	WrapGlobal(RLS, LS, "require");
	WrapGlobal(RLS, LS, "stats");
	WrapGlobal(RLS, LS, "UserSettings");
	WrapGlobal(RLS, LS, "settings");
	WrapGlobal(RLS, LS, "Vector3");
	WrapGlobal(RLS, LS, "Vector3int16");
	WrapGlobal(RLS, LS, "Enum");
	WrapGlobal(RLS, LS, "Faces");
	WrapGlobal(RLS, LS, "Color3");
	WrapGlobal(RLS, LS, "Object");
	WrapGlobal(RLS, LS, "RBXScriptSignal");
	WrapGlobal(RLS, LS, "RBXScriptConnection");
	WrapGlobal(RLS, LS, "ColorSequence");
	WrapGlobal(RLS, LS, "ColorSequenceKeypoint");
	WrapGlobal(RLS, LS, "NumberRange");
	WrapGlobal(RLS, LS, "NumberSequence");
	WrapGlobal(RLS, LS, "NumberSequenceKeypoint");
	WrapGlobal(RLS, LS, "PhysicalProperties");
	WrapGlobal(RLS, LS, "Ray");
	WrapGlobal(RLS, LS, "Rect");
	WrapGlobal(RLS, LS, "Region3");
	WrapGlobal(RLS, LS, "Region3int16");
	WrapGlobal(RLS, LS, "TweenInfo");
	WrapGlobal(RLS, LS, "UDim");
	WrapGlobal(RLS, LS, "UDim2");
	WrapGlobal(RLS, LS, "Vector2");
	WrapGlobal(RLS, LS, "error");
	WrapGlobal(RLS, LS, "warn");
	WrapGlobal(RLS, LS, "shared");
	WrapGlobal(RLS, LS, "print");
	WrapGlobal(RLS, LS, "printidentity");
	WrapGlobal(RLS, LS, "warn");
	WrapGlobal(RLS, LS, "delay");
	WrapGlobal(RLS, LS, "spawn");
	WrapGlobal(RLS, LS, "elapsedTime");
	WrapGlobal(RLS, LS, "LoadLibrary");
	WrapGlobal(RLS, LS, "PluginManager");
	WrapGlobal(RLS, LS, "require");
	WrapGlobal(RLS, LS, "stats");
	WrapGlobal(RLS, LS, "tick");
	WrapGlobal(RLS, LS, "time");
	WrapGlobal(RLS, LS, "typeof");
	WrapGlobal(RLS, LS, "UserSettings");
	WrapGlobal(RLS, LS, "version");
	WrapGlobal(RLS, LS, "wait");
	WrapGlobal(RLS, LS, "math");
	WrapGlobal(RLS, LS, "wait");
	WrapGlobal(RLS, LS, "warn");
	WrapGlobal(RLS, LS, "error");
	WrapGlobal(RLS, LS, "delay");
	WrapGlobal(RLS, LS, "elapsedTime");
	WrapGlobal(RLS, LS, "printidentity");
	WrapGlobal(RLS, LS, "LoadLibrary");
	WrapGlobal(RLS, LS, "PlayerGui");
	WrapGlobal(RLS, LS, "PluginManager");
	WrapGlobal(RLS, LS, "require");
	WrapGlobal(RLS, LS, "script");
	WrapGlobal(RLS, LS, "DebuggerManager");
	WrapGlobal(RLS, LS, "_VERSION");
	WrapGlobal(RLS, LS, "xpcall");
	WrapGlobal(RLS, LS, "unpack");
	WrapGlobal(RLS, LS, "newproxy");
	WrapGlobal(RLS, LS, "collectgarbage");
	WrapGlobal(RLS, LS, "assert");
	WrapGlobal(RLS, LS, "utf8");

	r_l_getglobal(RLS, "game");
	r_l_getfield(RLS, -1, "ContentProvider");
	ContentProvider = (int)r_l_touserdata(RLS, -1); //used internally for GetObjects btw
	r_l_pop(RLS, 2);

	std::cout << igreen << "Success!\n";

	std::cout << purple << "Aeonian Is Now Ready For Execution!\n";

	CommandSettings::Core::Initialized = true;
	CommandSettings::ChatHook::Active = true;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)aeopipe, NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)aeocmdpipe, NULL, NULL, NULL);

	luaL_dostring(LS, "print(\"Aeonian Loaded!\")");
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)LoadChatHook, NULL, NULL, NULL);
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExecuteChat, NULL, NULL, NULL);
}

















unsigned int ProtectSections(HMODULE Module
) {
	MODULEINFO ModuleInfo;
	GetModuleInformation(GetCurrentProcess(), Module, &ModuleInfo, sizeof(ModuleInfo));
	uintptr_t Address = reinterpret_cast<uintptr_t>(Module);
	uintptr_t TermAddress = Address + ModuleInfo.SizeOfImage;
	MEMORY_BASIC_INFORMATION MemoryInfo;


	while (Address < TermAddress) {
		VirtualQuery(reinterpret_cast<void*>(Address), &MemoryInfo, sizeof(MemoryInfo));
		if (MemoryInfo.State == MEM_COMMIT && (MemoryInfo.Protect & (PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY))) {
			DWORD OldProtection;
			VirtualProtect(reinterpret_cast<void*>(Address), MemoryInfo.RegionSize, PAGE_EXECUTE_READ, &OldProtection);
		}
		Address = reinterpret_cast<uintptr_t>(MemoryInfo.BaseAddress) + MemoryInfo.RegionSize;
	}

	VirtualQuery(reinterpret_cast<void*>(MemoryInfo.AllocationBase), &MemoryInfo, sizeof(MemoryInfo));
	if (MemoryInfo.State != MEM_COMMIT || !(MemoryInfo.Protect & PAGE_EXECUTE_READ))
		return 0x400;
	return MemoryInfo.RegionSize - 0x400;
}


__forceinline void UnlinkModule(HINSTANCE Module
) {
	unsigned long PEB_DATA = 0;
	_asm {
		pushad;
		pushfd;
		mov eax, fs:[30h]
			mov eax, [eax + 0Ch]
			mov PEB_DATA, eax

			InLoadOrderModuleList :
		mov esi, [eax + 0Ch]
			mov edx, [eax + 10h]

			LoopInLoadOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 18h]
			cmp ecx, Module
			jne SkipA
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp InMemoryOrderModuleList

			SkipA :
		cmp edx, esi
			jne LoopInLoadOrderModuleList

			InMemoryOrderModuleList :
		mov eax, PEB_DATA
			mov esi, [eax + 14h]
			mov edx, [eax + 18h]

			LoopInMemoryOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 10h]
			cmp ecx, Module
			jne SkipB
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp InInitializationOrderModuleList

			SkipB :
		cmp edx, esi
			jne LoopInMemoryOrderModuleList

			InInitializationOrderModuleList :
		mov eax, PEB_DATA
			mov esi, [eax + 1Ch]
			mov edx, [eax + 20h]

			LoopInInitializationOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 08h]
			cmp ecx, Module
			jne SkipC
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp Finished

			SkipC :
		cmp edx, esi
			jne LoopInInitializationOrderModuleList

			Finished :
		popfd;
		popad;
	}
}


BOOL APIENTRY DllMain(HMODULE Module, DWORD Reason, void* Reserved)
{
	switch (Reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(Module);
		UnlinkModule(Module);
		DWORD OldProtection;
		VirtualProtect(Module, 4096, PAGE_READWRITE, &OldProtection);
		ZeroMemory(Module, 4096);
		ProtectSections(Module);
		HANDLE hThread = NULL;
		HANDLE hDllMainThread = OpenThread(THREAD_ALL_ACCESS, NULL, GetCurrentThreadId());
		if (Reserved == NULL) {
			if (!(hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)maininit, NULL, NULL, NULL))) {
				CloseHandle(hDllMainThread);
				return FALSE;
			}
			CloseHandle(hThread);
		}
		return TRUE;
	}
}
