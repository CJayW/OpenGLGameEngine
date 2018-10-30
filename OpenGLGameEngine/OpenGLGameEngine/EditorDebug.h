#pragma once

#include <vector>
#include <array>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#define LogLevelLog 0
#define LogLevelWarning 1
#define LogLevelError 2

class EditorDebug {
public:
	EditorDebug();
	~EditorDebug();

	static void Render();

	static void Log(std::string message, int Level = LogLevelLog);

	template<class T>
	static void ErrorLog(T message) {
		Log(message, 2);
	}
	template<class T>
	static void PermLog(T message, int Level = LogLevelLog) {
		Log(message, Level);
	}
	static void Log(int message, int Level = LogLevelLog) {
		Log(std::to_string(message), Level);
	}
	static void Log(float message, int Level = LogLevelLog) {
		Log(std::to_string(message), Level);
	}
	static void Log(double message, int Level = LogLevelLog) {
		Log(std::to_string(message), Level);
	}
	static void Log(glm::vec3 message, int Level = LogLevelLog) {
		Log(glm::to_string(message), Level);
	}
	static void Log(glm::quat message, int Level = LogLevelLog) {
		Log(glm::to_string(message), Level);
	}
	static void SameLine(bool _addSpace = true) {
		sameLine = true;
		addSpace = _addSpace;
	}


private:
	static std::array<std::vector<std::string>, 3> LogMessages;

	static std::string names[3];

	static bool sameLine;
	static bool addSpace;
	static int lastLevel;

	static unsigned int currentDisplayLog;
};