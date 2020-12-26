#include "../Hooks.h"
#include "../../Overlay/Overlay.h"

static bool bInitialized = false;

BOOL WINAPI Hooks::wglSwapBuffersHook(_In_ HDC hDc) {
	if (!bInitialized) {
		Overlay::Init(hDc);
		DWORD dwTid = GetCurrentThreadId();
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Hooks::UpdateMessages), &dwTid, 0, nullptr);
		bInitialized = true;
	}

	Overlay::Render(hDc);

	return Hooks::oWglSwapBuffers(hDc);
}