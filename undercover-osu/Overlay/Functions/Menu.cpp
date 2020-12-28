#include "../Overlay.h"
#include "../../Config/Config.h"

static int currentTab = 0;

void Overlay::Toggle() {

	Menu::isOpen = !Menu::isOpen;

	if (!Menu::isOpen) {
		ImGui::GetIO().MouseDrawCursor = false;
		Input::RestoreRaw();
	}
	else {
		ImGui::GetIO().MouseDrawCursor = true;
		Input::DisableRaw();
	}
}

void Overlay::Render(HDC hDc) {
	if (!Menu::isOpen)
		return;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("undercover", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar); {
		ImGui::SetWindowSize(ImVec2(512, 512));

		ImGui::PushFont(Overlay::logoFont); {
			ImGui::SetCursorPos(ImVec2((512 / 2 - 55), 482));
			ImGui::Text("under");
			ImGui::SetCursorPos(ImVec2((512 / 2 - 55) + 65, 482));
			ImGui::TextColored(ImVec4(0.78, 0.074, 0.15, 1), "cover");
		}ImGui::PopFont();

		ImGui::PushFont(Overlay::menuIconFont); {
			ImGui::SetCursorPos(ImVec2(69, 0));
			if (ImGui::Button("H", ImVec2(75, 75)))
				currentTab = 0;

			ImGui::SetCursorPos(ImVec2(144, 0));
			if (ImGui::Button("C", ImVec2(75, 75)))
				currentTab = 1;

			ImGui::SetCursorPos(ImVec2(219, 0));
			if (ImGui::Button("I", ImVec2(75, 75)))
				currentTab = 2;

			ImGui::SetCursorPos(ImVec2(294, 0));
			if (ImGui::Button("D", ImVec2(75, 75)))
				currentTab = 3;

			ImGui::SetCursorPos(ImVec2(369, 0));
			if (ImGui::Button("G", ImVec2(75, 75)))
				currentTab = 4;
		}ImGui::PopFont();

		ImGui::Separator();

		ImGui::PushFont(Overlay::menuMainFont); {
			switch (currentTab) {
			case 0:
				ImGui::SetCursorPos(ImVec2(5, 84));
				ImGui::Text("Relax");
				ImGui::SetCursorPos(ImVec2(5, 109));
				ImGui::Checkbox("Enable", &Config::Relax::isEnabled);

				if (Config::Relax::isEnabled) {
					ImGui::SetCursorPos(ImVec2(100, 84));
					ImGui::Text("Style");
					ImGui::SetCursorPos(ImVec2(100, 104));
					ImGui::Combo("1.", &Config::Relax::tappingStyle, "TapX\0Alternate\0SingleTap");
					ImGui::SetCursorPos(ImVec2(100, 134));
					ImGui::Text("Max BPM");
					ImGui::SetCursorPos(ImVec2(100, 154));
					ImGui::SliderInt("2.", &Config::Relax::maxBpm, 10, 300);
					ImGui::SetCursorPos(ImVec2(100, 184));
					ImGui::Text("Alternation BPM");
					ImGui::SetCursorPos(ImVec2(100, 204));
					ImGui::SliderInt("3.", &Config::Relax::alternationBpm, 10, 300);
					ImGui::SetCursorPos(ImVec2(100, 234));
					ImGui::Checkbox("Manual Spinners", &Config::Relax::manualSpinners);
					ImGui::SetCursorPos(ImVec2(100, 264));
					ImGui::Checkbox("Wait Late", &Config::Relax::waitLate);
				}
				break;
			case 1:
				ImGui::SetCursorPos(ImVec2(5, 84));
				ImGui::Text("Timewarp");
				ImGui::SetCursorPos(ImVec2(5, 109));
				ImGui::Checkbox("Enable", &Config::Timewarp::isEnabled);

				if (Config::Timewarp::isEnabled) {
					ImGui::SetCursorPos(ImVec2(100, 84));
					ImGui::Text("Multiplier");
					ImGui::SetCursorPos(ImVec2(100, 104));
					ImGui::SliderFloat("1.", &Config::Timewarp::multiplier, 0.1f, 1.0f, "%.2f", 1);
				}
				break;
			case 2:
				ImGui::SetCursorPos(ImVec2(5, 84));
				ImGui::Text("Aim Assist");
				ImGui::SetCursorPos(ImVec2(5, 109));
				ImGui::Checkbox("Enable", &Config::AimAssist::isEnabled);

				if (Config::AimAssist::isEnabled) {
					ImGui::SetCursorPos(ImVec2(100, 84));
					ImGui::Text("Fov");
					ImGui::SetCursorPos(ImVec2(100, 104));
					ImGui::SliderFloat("1.", &Config::AimAssist::fov, 0.1f, 1.0f, "%.2f", 1);
				}
				break;
			case 3:
				ImGui::SetCursorPos(ImVec2(5, 84));
				ImGui::Text("Visuals");
				ImGui::SetCursorPos(ImVec2(5, 109));
				ImGui::Checkbox("Enable", &Config::Visuals::isEnabled);

				if (Config::Visuals::isEnabled) {
					ImGui::SetCursorPos(ImVec2(100, 84));
					ImGui::Checkbox("Disable Flashlight", &Config::Visuals::flashlight);
					ImGui::SetCursorPos(ImVec2(100, 114));
					ImGui::Checkbox("Disable Hidden", &Config::Visuals::hidden);
				}
				break;
			case 4:
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); {
				ImGui::SetCursorPos(ImVec2(5, 84));
				ImGui::Text("Misc");
				ImGui::SetCursorPos(ImVec2(100, 84));
				if (ImGui::Button("Save Config", ImVec2(110, 50)))
					Config::SaveConfig();
				ImGui::SetCursorPos(ImVec2(210, 84));
				if (ImGui::Button("Load Config", ImVec2(110, 50)))
					Config::LoadConfig();
			}ImGui::PopStyleColor();
				break;
			default: break;
			}
		}ImGui::PopFont();

	}ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}