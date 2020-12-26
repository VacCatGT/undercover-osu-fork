#include "../Hooks.h"
#include "../../Overlay/Overlay.h"

void Hooks::CreateHooks() {
	MH_Initialize();

	std::cout << "[ ~ ] attempting to hook required functions\n";

	void* pWglSwapBuffers = GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");

	if (MH_CreateHook(pWglSwapBuffers, Hooks::wglSwapBuffersHook, reinterpret_cast<LPVOID*>(&Hooks::oWglSwapBuffers)) == MH_OK)
		std::cout << "[ ! ] hooked wglSwapBuffers\n";
	else
		std::cout << "[ ! ] failed to hook wglSwapBuffers\n";

	MH_EnableHook(MH_ALL_HOOKS);
}