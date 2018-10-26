#pragma once

#include "Game.h"
#include "GameObject.h"

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();
	
	static std::string getNewUniqueName();

	static GameObject* Instantiate();
	static GameObject* Instantiate(GameObject* parent);

	static GameObject* GetObjectByName(std::string name);
	static GameObject* GetChildByName(GameObject* obj, std::string name);

	static void DestroyObject(GameObject* obj);
};