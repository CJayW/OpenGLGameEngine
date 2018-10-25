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

void GameObjectManager::DestroyObject(GameObject * obj)
{
	for (int i = 0; (size_t)i < Game::GameObjects.size(); i++) {

		if (Game::GameObjects[i] == obj) {
			delete obj;
			Game::GameObjects.erase(Game::GameObjects.begin() + i);
		}
	}
}
