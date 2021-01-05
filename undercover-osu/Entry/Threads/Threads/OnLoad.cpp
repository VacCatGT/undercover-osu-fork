#include "../Threads.h"
#include "../../../Hooks/Hooks.h"
#include "../../../Hacks/Hacks.h"

void Threads::OnLoad() {
#if _DEBUG
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
#endif // _DEBUG
	Hooks::CreateHooks();

	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Hacks::TimewarpThread), nullptr, 0, nullptr);
}
