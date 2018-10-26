#include "GameObjectManager.h"


GameObjectManager::GameObjectManager() {
}


GameObjectManager::~GameObjectManager() {
}

GameObject* GameObjectManager::Instantiate() {
	GameObject* obj = new GameObject();

	Game::GameObjects.push_back(obj);
	obj->Name = getNewUniqueName();
	return obj;
}

GameObject * GameObjectManager::Instantiate(GameObject * parent) {
	GameObject* obj = new GameObject();
	parent->children.push_back(obj);
	obj->parent = parent;
	obj->Name = getNewUniqueName();

	return obj;
}

std::string GameObjectManager::getNewUniqueName() {
	int nameIndex = 1;

	while (GetObjectByName(std::string("New Object ") + std::to_string(nameIndex)) != nullptr) {
		nameIndex++;
	}

	return std::string("New Object ") + std::to_string(nameIndex);
}

GameObject* GameObjectManager::GetObjectByName(std::string name) {
	
	for (auto obj : Game::GameObjects) {

		if (obj->Name == name) {
			return obj;
		} else {
			GameObject* ans = GetChildByName(obj, name);
			if (ans != nullptr) {
				return ans;
			}
		}
	}

	return nullptr;
}
GameObject* GameObjectManager::GetChildByName(GameObject* obj, std::string name) {
	for (auto cObj : obj->children) {
		if (cObj->Name == name) {
			return cObj;
		} else {
			GameObject* ans = GetChildByName(cObj, name);
			if (ans != nullptr) {
				return ans;
			}
		}
	}

	return nullptr;
}

void GameObjectManager::DestroyObject(GameObject * obj)
{
	if (obj->parent) {
		GameObject* parent = obj->parent;
		for (int i = 0; (size_t)i < parent->children.size(); i++) {

			if (parent->children[i] == obj) {
				delete obj;
				parent->children.erase(parent->children.begin() + i);
			}
		}
	}
	else {
		for (int i = 0; (size_t)i < Game::GameObjects.size(); i++) {

			if (Game::GameObjects[i] == obj) {
				delete obj;
				Game::GameObjects.erase(Game::GameObjects.begin() + i);
			}
		}
	}
}
