#include "LevelFileManager.h"

#include "GameObjectManager.h"
#include <iostream>
#include <fstream>

#include "Transform.h"

#include "Camera.h"
#include "MeshRenderer.h"

#include "CameraMovement.h"
#include "TestMove.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

LevelFileManager::LevelFileManager() {
}

LevelFileManager::~LevelFileManager() {
}

void LevelFileManager::loadLevel() {

	std::string file;

	std::ifstream ip("Resources/Levels/Level.txt");
	
	while (ip.good()) {
		std::getline(ip, file);
		
		if (file == "return") {
			ip.close();
			return;
		} else if (file == "") {
			continue;
		} else if (file[0] == '/' && file[1] == '/') {
			continue;
		}

		GameObject* obj = GameObjectManager::Instantiate();

		for (auto componentString : splitBy(file, ':')) {
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
				glm::vec3 rot;
				rot.x = glm::radians(std::stof(params[0]));
				rot.y = glm::radians(std::stof(params[1]));
				rot.z = glm::radians(std::stof(params[2]));

				obj->transform->rotation = glm::quat(rot);
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
				//DirectionalLight
			case 7:
				obj->addComponent<DirectionalLight>(componentInfo[1]);

				break;
				//PointLight
			case 8:
				obj->addComponent<PointLight>(componentInfo[1]);

				break;
				//spotLight
			case 9:
				obj->addComponent<SpotLight>(componentInfo[1]);
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


	for (int i = 0; (size_t)i < componentArr->capacity(); i++) {
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
	"TestMove",			
	"DirectionalLight",	
	"PointLight",		
	"SpotLight"			
};