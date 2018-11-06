#include "LocalLevelFileManager.h"
#include "Editor Location/EditorDebug.h"
#include <iostream>
#include <string>

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

//AddNewComponentsHere

	return false;
}