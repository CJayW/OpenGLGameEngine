#include "GameObjectManager.h"


GameObjectManager::GameObjectManager() {
}


GameObjectManager::~GameObjectManager() {
}

GameObject* GameObjectManager::Instantiate() {
	GameObject* obj = new GameObject();

	Game::GameObjects.push_back(obj);
	return obj;
}

GameObject* GameObjectManager::GetObjectByName(std::string name) {
	
	for (auto obj : Game::GameObjects) {

		if (obj->Name == name)
			return obj;
	}

	return nullptr;
}
