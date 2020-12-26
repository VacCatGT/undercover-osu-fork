#pragma once
#include <list>
#include <windows.h>

struct MemoryRegion
{
	DWORD BaseAddress;
	SIZE_T RegionSize;
	DWORD State;
	DWORD Protect;
	DWORD Type;
	
	MemoryRegion(MEMORY_BASIC_INFORMATION32 mbi)
	{
		BaseAddress = mbi.BaseAddress;
		RegionSize = mbi.RegionSize;
		State = mbi.State;
		Protect = mbi.Protect;
		Type = mbi.Type;
	}
};

class OsuProcess
{
	std::list<MemoryRegion> memoryRegions;
	void dumpMemoryRegions();
public:
	OsuProcess();
	uintptr_t FindSignature(const char* pattern, const char* mask);
};
