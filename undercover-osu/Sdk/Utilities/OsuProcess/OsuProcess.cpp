#include "../OsuProcess.h"
#include <iostream>

void OsuProcess::dumpMemoryRegions()
{
	memoryRegions.clear();

	MEMORY_BASIC_INFORMATION32 mbi;
	LPCVOID address = 0;

	while (VirtualQueryEx(GetCurrentProcess(), address, reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&mbi), sizeof(mbi)) != 0)
	{

		if (mbi.State == MEM_COMMIT && mbi.Protect >= 0x10 && mbi.Protect <= 0x80) {
			memoryRegions.push_back(*new MemoryRegion(mbi));
		}
		address = reinterpret_cast<LPCVOID>(mbi.BaseAddress + mbi.RegionSize);
	}
}

OsuProcess::OsuProcess()
{
	dumpMemoryRegions();
}

uintptr_t OsuProcess::FindSignature(const char* pattern, const char* mask)
{
	for (const auto& region : memoryRegions)
	{
		size_t patternLength = strlen(mask);

		for (uintptr_t i = 0; i < region.RegionSize - patternLength; i++)
		{
			bool found = true;
			for (uintptr_t j = 0; j < patternLength; j++)
			{
				if (mask[j] != '?' && pattern[j] != *(char*)(region.BaseAddress + i + j))
				{
					found = false;
					break;
				}
			}

			if (found) {
				return region.BaseAddress + i;
			}
		}
	}
	
	return NULL;
}