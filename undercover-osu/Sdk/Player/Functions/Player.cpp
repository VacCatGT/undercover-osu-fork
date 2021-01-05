#include "../Player.h"
#include "../../../Sdk/sdk.h"
#include <iostream>

//cum in my asshole and call me daddy <3
//i missed something...

uintptr_t playerPointer = *(uintptr_t*)(Process.FindSignature("\xFF\x50\x0C\x8B\xD8\x8B\x15", "xxxxxxx") + 0x7);

uintptr_t Player::GetBaseAddress() {
	return *(uintptr_t*)(playerPointer);
}

bool Player::asyncLoadComplete()
{
	return *(bool*)(GetBaseAddress() + 0x182);
}

bool Player::IsLoaded()
{
	return GetBaseAddress() != NULL && asyncLoadComplete();
}

bool Player::IsReplayMode()
{
	return *(bool*)(GetBaseAddress() + 0x17A);
}

int Player::GetAudioCheckCount() {
	return *(int*)(GetBaseAddress() + 0x14C);
}

void Player::SetAudioCheckCount(int value) {
	*(int*)(GetBaseAddress() + 0x14C) = value;
}