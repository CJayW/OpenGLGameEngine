#pragma once

#include "Game.h"
#include "GameObject.h"

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();
	
	static GameObject* Instantiate();

	static GameObject* GetObjectByName(std::string name);

};