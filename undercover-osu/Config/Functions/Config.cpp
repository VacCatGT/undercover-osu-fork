#include "../Config.h"
#include <SimpleIni.h>

CSimpleIniA Ini;

void Config::SaveConfig() {
		Ini.SetBoolValue("Undercover", "OwO Whats This?", true);
		Ini.SetBoolValue("Aim Assist", "isEnabled", Config::AimAssist::isEnabled);
		Ini.SetBoolValue("Relax", "isEnabled", Config::Relax::isEnabled);
		Ini.SetBoolValue("Timewarp", "isEnabled", Config::Timewarp::isEnabled);
		Ini.SetBoolValue("Visuals", "isEnabled", Config::Visuals::isEnabled);

		Ini.SetDoubleValue("Timewarp", "multiplier", Config::Timewarp::multiplier);

		Ini.SetDoubleValue("Aim Assist", "fov", Config::AimAssist::fov);

		Ini.SetBoolValue("Visuals", "disableHidden", Config::Visuals::hidden);
		Ini.SetBoolValue("Visuals", "disableFlashlight", Config::Visuals::flashlight);

		Ini.SetBoolValue("Relax", "manualSpinners", Config::Relax::manualSpinners);
		Ini.SetBoolValue("Relax", "waitLate", Config::Relax::waitLate);
		Ini.SetLongValue("Relax", "tappingStyle", Config::Relax::tappingStyle);
		Ini.SetLongValue("Relax", "maxBpm", Config::Relax::maxBpm);
		Ini.SetLongValue("Relax", "alternationBpm", Config::Relax::alternationBpm);

		Ini.SaveFile("undercover.ini");
}

void Config::LoadConfig() {
	Ini.LoadFile("undercover.ini");

	Config::AimAssist::isEnabled = Ini.GetBoolValue("Aim Assist", "isEnabled");
	Config::Relax::isEnabled = Ini.GetBoolValue("Relax", "isEnabled");
	Config::Timewarp::isEnabled = Ini.GetBoolValue("Timewarp", "isEnabled");
	Config::Visuals::isEnabled = Ini.GetBoolValue("Visuals", "isEnabled");

	Config::Timewarp::multiplier = Ini.GetDoubleValue("Timewarp", "multiplier");

	Config::AimAssist::fov = Ini.GetDoubleValue("Aim Assist", "fov");

	Config::Visuals::hidden = Ini.GetBoolValue("Visuals", "disableHidden");
	Config::Visuals::flashlight = Ini.GetBoolValue("Visuals", "disableFlashlight");

	Config::Relax::manualSpinners = Ini.GetBoolValue("Relax", "manualSpinners");
	Config::Relax::waitLate = Ini.GetBoolValue("Relax", "waitLate");
	Config::Relax::tappingStyle = Ini.GetLongValue("Relax", "tappingStyle");
	Config::Relax::maxBpm = Ini.GetLongValue("Relax", "maxBpm");
	Config::Relax::alternationBpm = Ini.GetLongValue("Relax", "alternationBpm");
}