#pragma once
#include "F:/OpenGLGameEngine/OpenGLGameEngine/OpenGLGameEngine/GameObject.h"

class LocalLevelFileManager {
public:
	LocalLevelFileManager();
	~LocalLevelFileManager();

	static bool LoadLevel(std::string name, std::string params, GameObject* obj);
};
