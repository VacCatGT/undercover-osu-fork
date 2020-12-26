#include "../Input.h"

void Input::DisableRaw() {

	Input::BackupRaw();

	if (Input::uiDeviceCount == -1)
		return;

	if (!Input::uiDeviceCount)
		return;

	for (unsigned int i = 0; i < Input::uiDeviceCount; i++) {
		RAWINPUTDEVICE device;
		memcpy(&device, Input::pDevices + i, sizeof(RAWINPUTDEVICE));
		device.dwFlags = RIDEV_REMOVE;
		device.hwndTarget = NULL;
		RegisterRawInputDevices(&device, 1, sizeof(RAWINPUTDEVICE));
	}
}

void Input::BackupRaw() {
	Input::uiDeviceCount = -1;
	GetRegisteredRawInputDevices(NULL, &Input::uiDeviceCount, sizeof(RAWINPUTDEVICE));

	if (Input::pDevices)
		delete Input::pDevices;

	Input::pDevices = new RAWINPUTDEVICE[Input::uiDeviceCount];
	GetRegisteredRawInputDevices(Input::pDevices, &Input::uiDeviceCount, sizeof(RAWINPUTDEVICE));
}

void Input::RestoreRaw() {
	if (Input::uiDeviceCount == -1)
		return;

	if (!Input::uiDeviceCount)
		return;

	RegisterRawInputDevices(Input::pDevices, Input::uiDeviceCount, sizeof(RAWINPUTDEVICE));
}