#include "LevelFileManager.h"

#include "GameObjectManager.h"
#include <iostream>
#include <fstream>

#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "CameraMovement.h"
#include "TestMove.h"

LevelFileManager::LevelFileManager() {
}

LevelFileManager::~LevelFileManager() {
}

void LevelFileManager::loadLevel() {
	std::string file;
	/*
	transform(0,0,0)-MeshRenderer( )
	transform(0,0,0)-Camera( )
	*/

	std::ifstream ip("Level.txt");
	
	while (ip.good()) {
		std::getline(ip, file);
		
		if (file == "return") {
			ip.close();
			return;
		} else if (file == "") {
			continue;
		}

		GameObject* obj = GameObjectManager::Instantiate();

		for (auto componentString : splitBy(file, ':')) {
			//std::cout << componentString << std::endl;
			std::vector<std::string> componentInfo = splitBy(componentString, '(');

			std::vector<std::string> params;

			switch (LevelFileManager::findComponentIndex(componentInfo[0])) {
				//Translate
			case 0:
				params = splitBy(componentInfo[1], ',');
				obj->transform->position.x = std::stof(params[0]);
				obj->transform->position.y = std::stof(params[1]);
				obj->transform->position.z = std::stof(params[2]);

				break;
				//Rotate
			case 1:
				params = splitBy(componentInfo[1], ',');
				obj->transform->rotation.y = std::stof(params[1]);
				obj->transform->rotation.x = std::stof(params[0]);
				obj->transform->rotation.z = std::stof(params[2]);
				obj->transform->rotation.w = std::stof(params[3]);

				break;
				//Scale
			case 2:
				params = splitBy(componentInfo[1], ',');
				obj->transform->scale.x = std::stof(params[0]);
				obj->transform->scale.y = std::stof(params[1]);
				obj->transform->scale.z = std::stof(params[2]);

				break;
				//MeshRenderer
			case 3:
				obj->addComponent<MeshRenderer>(componentInfo[1]);

				break;
				//Camera
			case 4:
				Game::camera = obj->addComponent<Camera>(componentInfo[1]);

				break;
				//CameraMovement
			case 5:
				obj->addComponent<CameraMovement>(componentInfo[1]);

				break;
				//TestMove
			case 6:
				obj->addComponent<TestMove>(componentInfo[1]);

				break;
			case -1:
				std::cout << "Failed To Find Component: '" << componentInfo[0] << "'" << std::endl;

				break;
				//-1 Fail
			default:
				std::cout << "This component doesnt seem to have a full implamentation: '" << componentInfo[0] << "' "<< LevelFileManager::findComponentIndex(componentInfo[0]) << std::endl;
				break;
			}
		}
	}

	ip.close();
}

std::vector<std::string> LevelFileManager::splitBy(std::string str, char div) {
	
	std::vector<std::string> splitVals;
	splitVals.push_back("");
	
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == div) {
			splitVals.push_back("");
		} else {
			splitVals[splitVals.size() -1] += str[i];
		}
	}
	return splitVals;
}

int LevelFileManager::findComponentIndex(std::string compName ) {
	if (compName == "")
		return -1;

	for (int i = 0; i < componentArr->size(); i++) {
		if (compName == componentArr[i])
			return i;
	}

	return -1;
}

std::string LevelFileManager::componentArr[] = {
	"Translate",
	"Rotate",
	"Scale",
	"MeshRenderer",
	"Camera",
	"CameraMovement",
	"TestMove"
};