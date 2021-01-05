#include "../Threads.h"
#include "../../../Hooks/Hooks.h"

#include "../../../Sdk/Audio/OsuAudio.h"

void Threads::OnLoad() {
#if _DEBUG
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
#endif // _DEBUG
	Hooks::CreateHooks();

	while (1)
		Audio::SetRateMultiplier(Config::Timewarp::multiplier);
}