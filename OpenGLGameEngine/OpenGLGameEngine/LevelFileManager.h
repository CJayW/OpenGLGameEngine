#pragma once
#include <vector>

class LevelFileManager {
public:
	LevelFileManager();
	~LevelFileManager();

	static void loadLevel();

	static std::vector<std::string> splitBy(std::string str, char div);
	
	static int findComponentIndex(std::string compName);

	static std::string componentArr[];
};

