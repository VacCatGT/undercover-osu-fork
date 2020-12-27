#include <Windows.h>
#include "../Utilities/OsuProcess.h"
#include "../../Config/Config.h"

class Bass {
private:
   typedef BOOL(__stdcall* ChannelSetAttribute_t)(DWORD handle, DWORD attrib, float value);
public:
	static inline ChannelSetAttribute_t ChannelSetAttribute = reinterpret_cast<ChannelSetAttribute_t>(GetProcAddress(GetModuleHandleA("bass.dll"), "BASS_ChannelSetAttribute"));
};

class Audio {
public:
	static void SetRate(double rate);
};