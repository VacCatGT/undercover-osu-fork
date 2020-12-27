#include "../OsuAudio.h"
#include "../../../Sdk/Utilities/OsuProcess.h"
#include <iostream>

OsuProcess Process;

uintptr_t trackPointer = *(uintptr_t*)(Process.FindSignature("\x56\x83\xEC\x38\x83\x3D", "xxxxxx") + 0x6);
//don't use outside of testing branch. we'll figure out better approach later.
uintptr_t modeAddress = *(uintptr_t*)(Process.FindSignature("\x8D\x45\xBC\x89\x46\x0C\x83\x3D", "xxxxxxxx") + 0x8);

uintptr_t baseAddress() {
    return *(uintptr_t*)trackPointer;
}

int trackHandle() {
    return *(int*)(baseAddress() + 0x10);
}

float initFreq() {
    return *(float*)(baseAddress() + 0x3C);
}

bool nightcore() {
    return !*(bool*)(baseAddress() + 0x1B);
}

double osuTrackRate()
{
    return *(double*)(baseAddress() + 0x1C);
}

void Audio::SetRateMultiplier(double multiplier) {
    if (*(int*)modeAddress != 2)
        return;
	
    SetRate(osuTrackRate() * multiplier);
}

void Audio::SetRate(double rate) {
    if (*(int*)modeAddress != 2)
        return;
	
    if (rate < 1)
        rate = 1;
	
    if (nightcore()) {
        Bass::ChannelSetAttribute(trackHandle(), 1, (float)(initFreq() * rate / 100.0));
        Bass::ChannelSetAttribute(trackHandle(), 65536, 0);
    }
    else {
        Bass::ChannelSetAttribute(trackHandle(), 1, initFreq());
        Bass::ChannelSetAttribute(trackHandle(), 65536, (float)(rate - 100.0));
    }
}