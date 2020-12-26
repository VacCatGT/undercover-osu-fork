#include <minhook.h>
#include <iostream>

typedef BOOL(WINAPI* fnWglSwapBuffers) (_In_ HDC hDc);

class Hooks {
public:
	static void CreateHooks();
private:
	static inline HHOOK GetMsgProcHook;
	static inline fnWglSwapBuffers oWglSwapBuffers;
	static inline HWND hWnd;
	static void UpdateMessages(DWORD* dwTid);
	static LRESULT CALLBACK MsgProc(int nCode, WPARAM wParam, LPARAM lParam);
	static BOOL WINAPI wglSwapBuffersHook(_In_ HDC hDc);
};