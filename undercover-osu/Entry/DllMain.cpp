#include <Windows.h>
#include <iostream>

#include "Threads/Threads.h"

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hInstance);
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Threads::OnLoad), nullptr, 0, nullptr);
		break;
	default: break;
	}
	return TRUE;
}
