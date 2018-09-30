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