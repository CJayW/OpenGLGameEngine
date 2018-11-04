#include "LocalLevelFileManager.h"
#include "F:/OpenGLGameEngine/OpenGLGameEngine/OpenGLGameEngine/EditorDebug.h"
#include <iostream>
#include <string>

#include "move.h" 
//IncludeHere

LocalLevelFileManager::LocalLevelFileManager() {
}

LocalLevelFileManager::~LocalLevelFileManager() {
}

#define checkComp(compType) \
if(componentName == compType::name){\
	obj->addComponent<compType>(params);\
	return true;\
}

bool LocalLevelFileManager::LoadLevel(std::string componentName, std::string params, GameObject* obj) {
	checkComp(move);
//AddNewComponentsHere

	return false;
}