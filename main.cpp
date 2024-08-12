#include <windows.h>
#include <fstream>
#include "nya_commonhooklib.h"

auto CopyString = (void*(__thiscall*)(void*, const char*, int))0x4023E0;
void* __fastcall LogLUAErr(void* a1, void*, const char* a2, int a3) {
	MessageBoxA(nullptr, a2, "Runtime error", 0x10);
	exit(0);
}

auto lua_tolstring = (const char*(*)(void*, int, void*))0x6332B0;
void* LogLUALoadErr(void* a1, int a2, void* a3) {
	MessageBoxA(nullptr, lua_tolstring(a1, a2, a3), "Load error", 0x10);
	exit(0);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	switch( fdwReason ) {
		case DLL_PROCESS_ATTACH: {
			if (NyaHookLib::GetEntryPoint() != 0x24CEF7) {
				MessageBoxA(nullptr, "Unsupported game version! Make sure you're using the Steam GFWL version (.exe size of 4242504 bytes)", "nya?!~", MB_ICONERROR);
				exit(0);
				return TRUE;
			}

			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x5DE354, &LogLUAErr);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x5DE2AD, &LogLUALoadErr);
		} break;
		default:
			break;
	}
	return TRUE;
}