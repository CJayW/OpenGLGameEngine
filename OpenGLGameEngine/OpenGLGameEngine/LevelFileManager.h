#pragma once
#include <vector>

#include "GameObject.h"

class LevelFileManager {
public:
	LevelFileManager();
	~LevelFileManager();

	static void loadLevel();

	static std::vector<std::string> splitBy(std::string str, char div);

};