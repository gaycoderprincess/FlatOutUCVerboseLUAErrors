#include <windows.h>
#include <fstream>
#include "nya_commonhooklib.h"

auto CopyString = (void*(__thiscall*)(void*, const char*, int))0x4023E0;
void* __fastcall LogLUAErr(void* a1, void*, const char* a2, int a3) {
	MessageBoxA(nullptr, a2, "Fatal error", 0x10);
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
		} break;
		default:
			break;
	}
	return TRUE;
}