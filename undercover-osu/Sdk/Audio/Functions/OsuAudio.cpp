#include "../OsuAudio.h"
#include "../../../Sdk/sdk.h"
#include <iostream>

uintptr_t trackPointer = *(uintptr_t*)(Process.FindSignature("\x56\x83\xEC\x38\x83\x3D", "xxxxxx") + 0x6);

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

double Audio::OsuTrackRate() {
    return *(double*)(baseAddress() + 0x1C);
}

void Audio::SetRateMultiplier(double multiplier) {
    SetRate(OsuTrackRate() * multiplier);
}

void Audio::SetRate(double rate) {
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