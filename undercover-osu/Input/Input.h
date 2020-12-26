#include <Windows.h>
#pragma warning( disable : 6278 )

class Input {
public:
	static void DisableRaw();
	static void BackupRaw();
	static void RestoreRaw();
private:
	static inline RAWINPUTDEVICE* pDevices;
	static inline UINT uiDeviceCount;
};