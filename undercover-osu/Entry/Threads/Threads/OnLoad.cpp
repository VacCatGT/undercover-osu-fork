#include "../Threads.h"
#include "../../../Hooks/Hooks.h"

#include "../../../Sdk/Audio/OsuAudio.h"
#include "../../../Sdk/Player/Player.h"
#include "../../../Config/Config.h"

void Threads::OnLoad() {
#if _DEBUG
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
#endif // _DEBUG
	Hooks::CreateHooks();

	while (1) {
		if (Player::IsLoaded()) {
			if (Config::Timewarp::isEnabled) {
				Audio::SetRateMultiplier(Config::Timewarp::multiplier);

				Player::SetAudioCheckCount(0);
			}
			else {
				Audio::SetRate(Audio::OsuTrackRate());
			}
		}

		Sleep(1);
	}
}
