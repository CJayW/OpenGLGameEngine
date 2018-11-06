#include "EditorDebug.h"

#include "imGUI/imgui.h"

EditorDebug::EditorDebug() {
	currentDisplayLog = 0;
}

EditorDebug::~EditorDebug() {
}

std::array<std::vector<std::string>, 3> EditorDebug::LogMessages;

std::string EditorDebug::names[3] = { "Log", "Warning", "Error" };

unsigned int EditorDebug::currentDisplayLog;

bool EditorDebug::sameLine;
bool EditorDebug::addSpace;
int EditorDebug::lastLevel;

void EditorDebug::Render() {

	//TODO ImGuiListClipper 
	//https://github.com/ocornut/imgui/issues/1438

	ImGui::Begin("Debug Log",(bool *)0, ImGuiWindowFlags_NoScrollbar);
	{
		for (unsigned int i = 0; i < LogMessages.size(); i++) {
			if (ImGui::Button((names[i] + std::string(" ") + std::to_string(LogMessages[i].size())).c_str())) {
				currentDisplayLog = i;
			}
			ImGui::SameLine();
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear Logs")) {
			for (int i = 0; i < 3; i++) {
				LogMessages[i].clear();
			}
		}
	}
	//the log that currently being shown
	ImGui::Text((names[currentDisplayLog] + std::string(":")).c_str());

	ImGui::Separator();

	//shows the logs 
	ImGui::BeginChild(1);
	for (std::string str : LogMessages[currentDisplayLog]) {
		ImGui::Text(str.c_str());
	}

	ImGui::EndChild();

	ImGui::End();

}

void EditorDebug::Log(std::string message, int Level) {
	
	if (sameLine) {
		LogMessages[lastLevel][LogMessages[lastLevel].size() -1] += ((addSpace) ? std::string(" ") : std::string(""))  + message;
	} else {
		LogMessages[Level].push_back(message);
	}
	lastLevel = Level;

	sameLine = false;
	addSpace = false;
}
