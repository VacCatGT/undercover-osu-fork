#include "../Hooks.h"
#include "../../Overlay/Overlay.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);

LRESULT CALLBACK Hooks::MsgProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode > 0)
		return CallNextHookEx(Hooks::GetMsgProcHook, nCode, wParam, lParam);

	MSG* pMsg = reinterpret_cast<MSG*>(lParam);

	switch (wParam == PM_REMOVE) {
	case TRUE:
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_HOME)
			Overlay::Toggle();

		if (Menu::isOpen)
			ImGui_ImplWin32_WndProcHandler(pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam);
		break;
	default:
		break;
	}

	switch (Menu::isOpen) {
	case TRUE:
		if (pMsg->message == WM_CHAR) {
			pMsg->message = WM_NULL;
			return TRUE;
		}
		if ((WM_MOUSEFIRST <= pMsg->message && pMsg->message <= WM_MOUSELAST)) {
			pMsg->message = WM_NULL;
			return TRUE;
		}
		break;
	default:
		break;
	}

	return CallNextHookEx(Hooks::GetMsgProcHook, nCode, wParam, lParam);
}

void Hooks::UpdateMessages() {

	while(!Hooks::GetMsgProcHook)
		Hooks::GetMsgProcHook = SetWindowsHookExW(3, Hooks::MsgProc, GetModuleHandleW(NULL), Hooks::threadId);

	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}