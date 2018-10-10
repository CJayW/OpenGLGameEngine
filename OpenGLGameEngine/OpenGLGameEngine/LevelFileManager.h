#pragma once
#include <vector>

#include "GameObject.h"

#include <glm/glm.hpp>

class LevelFileManager {
public:
	LevelFileManager();
	~LevelFileManager();

	static void loadLevel();

	static std::vector<std::string> splitBy(std::string str, char div);

	static glm::vec3 stringToVec3(std::string str);
};