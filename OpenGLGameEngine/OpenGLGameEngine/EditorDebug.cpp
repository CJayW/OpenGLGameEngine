#include "EditorDebug.h"

#include "imGUI/imgui.h"

EditorDebug::EditorDebug() {
	currentDisplayLog = 0;
}

EditorDebug::~EditorDebug() {
}

std::vector<std::string> EditorDebug::LogMessages;
std::vector<std::string> EditorDebug::warningLog;
std::vector<std::string> EditorDebug::ErrorLog;

unsigned int EditorDebug::currentDisplayLog;

void EditorDebug::Render() {
	ImGui::Begin("Debug Log",(bool *)0, ImGuiWindowFlags_NoScrollbar);

	if (ImGui::Button((std::string("Log ") + std::to_string(LogMessages.size())).c_str())) {
		currentDisplayLog = 0;
	} 
	ImGui::SameLine();
	if (ImGui::Button((std::string("Warning ") + std::to_string(warningLog.size())).c_str())) {
		currentDisplayLog = 1;
	} 
	ImGui::SameLine();
	if (ImGui::Button((std::string("Error ") + std::to_string(ErrorLog.size())).c_str())) {
		currentDisplayLog = 2;
	}
	ImGui::SameLine();
	if (ImGui::Button("Clear Logs")) {
		LogMessages.clear();
		warningLog.clear();
		ErrorLog.clear();
	}

	switch (currentDisplayLog)
	{
	case 0:
		ImGui::Text("Log:");

		break;
	case 1:
		ImGui::Text("Warning:");

		break;
	case 2:
		ImGui::Text("Error:");

		break;
	}

	ImGui::Separator();

	ImGui::BeginChild(1);
	{
		switch (currentDisplayLog)
		{
		case 0:
			for (std::string str : LogMessages) {
				ImGui::Text(str.c_str());
			}

			break;
		case 1:
			for (std::string str : warningLog) {
				ImGui::Text(str.c_str());
			}

			break;
		case 2:
			for (std::string str : ErrorLog) {
				ImGui::Text(str.c_str());
			}

			break;
		}
	}
	ImGui::EndChild();




	ImGui::End();
}

void EditorDebug::Log(std::string message, int Level) {

	switch (Level)
	{
	case 0:
		LogMessages.push_back(message);
		break;
	case 1:
		warningLog.push_back(message);
		break;
	case 2:
		ErrorLog.push_back(message);
		break;
	default:
		Log(std::string("Error : Cannot find log Level: ") + std::to_string(Level), 2);
		break;
	}
}
