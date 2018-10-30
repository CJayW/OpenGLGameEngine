#pragma once

#include <vector>
#include <string>

#define LogLevelLog 0
#define LogLevelWarning 1
#define LogLevelError 2


class EditorDebug {
public:
	EditorDebug();
	~EditorDebug();

	static void Render();

	static void Log(std::string message, int Level = LogLevelLog);

private:
	static std::vector<std::string> LogMessages;
	static std::vector<std::string> warningLog;
	static std::vector<std::string> ErrorLog;

	static unsigned int currentDisplayLog;
};