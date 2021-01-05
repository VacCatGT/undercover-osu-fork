#include <Windows.h>
#include "../Utilities/OsuProcess.h"

class Player {
public:
	static int GetAudioCheckCount();
	static void SetAudioCheckCount(int value);
private:
	static uintptr_t GetBaseAddress();
};