#include "../Hacks.h"

void Hacks::TimewarpThread() {
	while (1) {
		if (Player::IsLoaded() && !Player::IsReplayMode()) {
			if (Config::Timewarp::isEnabled) {
				Audio::SetRateMultiplier(Config::Timewarp::multiplier);

				Player::SetAudioCheckCount(0);
				Player::SetDateTimeCheckCount(0);
			}
			else {
				Audio::SetRate(Audio::OsuTrackRate());
			}
		}
		Sleep(1);
	}
}