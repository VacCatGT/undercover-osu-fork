#include "../OsuAudio.h"
#include "../../../Sdk/Utilities/OsuProcess.h"
#include <iostream>

OsuProcess Process;

uintptr_t baseAddress = *(uintptr_t*)(Process.FindSignature("\x56\x83\xEC\x38\x83\x3D", "xxxxxx") + 0x6);

int trackHandle = *(int*)(*(uintptr_t*)(baseAddress) + 0x10);
bool nightcore = *(bool*)(*(uintptr_t*)(baseAddress) + 0x1B);
float initFreq = *(float*)(*(uintptr_t*)(baseAddress) + 0x3C);

void Audio::SetRate(double rate) {
	std::cout << trackHandle << std::endl;
}