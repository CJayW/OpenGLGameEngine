#pragma once
#include <vector>

#include "GameObject.h"

#include <glm/glm.hpp>

class LevelFileManager {
public:
	LevelFileManager();
	~LevelFileManager();


	static bool checkLevelName(std::string name);

	static void loadLevel(std::string fileName);

	static bool saveLevel(std::string fileName);

	static void clearLevel();

	static std::string levelName;

	static std::string objToString(GameObject* obj, unsigned int childLevel);

	static std::string removeFirstChar(std::string string);

	static std::string vec3ToSaveString(glm::vec3 vec);

	static std::vector<std::string> splitBy(std::string str, char div);

	static glm::vec3 stringToVec3(std::string str);
};