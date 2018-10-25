#include "LevelFileManager.h"

#include "GameObjectManager.h"
#include <iostream>
#include <fstream>

#include "Transform.h"

#include "Camera.h"
#include "MeshRenderer.h"
#include "IconRenderer.h"

#include "CameraMovement.h"
#include "TestMove.h"
#include "Rigidbody.h"

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
	//while there are more lines
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

			//sets the name of the object
			if (componentInfo.size() < 2) {
				obj->Name = componentInfo[0];
				continue;
			}

			std::vector<std::string> params;

			std::string componentName = componentInfo[0];

			if		(componentName == "Translate") {
				//Translate
				params = splitBy(componentInfo[1], ',');
				obj->transform->position.x = std::stof(params[0]);
				obj->transform->position.y = std::stof(params[1]);
				obj->transform->position.z = std::stof(params[2]);
				//Rotate
			} 
			else if (componentName == "Rotate"){

				params = splitBy(componentInfo[1], ',');
				glm::vec3 rot;
				rot.x = glm::radians(std::stof(params[0]));
				rot.y = glm::radians(std::stof(params[1]));
				rot.z = glm::radians(std::stof(params[2]));

				obj->transform->rotation = glm::quat(rot);
			}
			else if (componentName == "Scale") {
				//Scale

				params = splitBy(componentInfo[1], ',');
				obj->transform->scale.x = std::stof(params[0]);
				obj->transform->scale.y = std::stof(params[1]);
				obj->transform->scale.z = std::stof(params[2]);
			}
			else if (componentName == MeshRenderer::name) {
				//MeshRenderer
				obj->addComponent<MeshRenderer>(componentInfo[1]);
			}
			else if (componentName == Camera::name) {
				//Camera
				Game::camera = obj->addComponent<Camera>(componentInfo[1]);
			}
			else if (componentName == CameraMovement::name) {
				//CameraMovement
				obj->addComponent<CameraMovement>(componentInfo[1]);
			}
			else if (componentName == TestMove::name) {
				//TestMove
				obj->addComponent<TestMove>(componentInfo[1]);
			}
			else if (componentName == DirectionalLight::name) {
				//DirectionalLight
				obj->addComponent<DirectionalLight>(componentInfo[1]);
			}
			else if (componentName == PointLight::name) {
				//PointLight
				obj->addComponent<PointLight>(componentInfo[1]);
			}
			else if (componentName == SpotLight::name) {
				//spotLight
				obj->addComponent<SpotLight>(componentInfo[1]);
			}
			else if (componentName == Rigidbody::name) {
				//ComponentTemplate
				obj->addComponent<Rigidbody>(componentInfo[1]);
			} 
			else if (componentName == IconRenderer::name) {
				//Icon Renderer
				obj->addComponent<IconRenderer>(componentInfo[1]);
			}
			/*
			else if (componentName == ComponentTemplate::name) {
				//ComponentTemplate
				obj->addComponent<ComponentTemplate>(componentInfo[1]);
			}
			*/
			else {

				std::cout << "Failed To Find Component: '" << componentName << "'" << std::endl;
			}
		}
	}
	ip.close();
}


std::vector<std::string> LevelFileManager::splitBy(std::string str, char div) {
	
	std::vector<std::string> splitVals;
	splitVals.push_back("");
	for (int i = 0; (size_t)i < str.length(); i++) {
		if (str[i] == div) {
			splitVals.push_back("");
		} else {
			splitVals[splitVals.size() -1] += str[i];
		}
	}
	return splitVals;
}


glm::vec3 LevelFileManager::stringToVec3(std::string str) {
	std::vector<std::string> split = splitBy(str, ' ');

	if (split.size() < 3) {
		return glm::vec3(0);
	}

	glm::vec3 vec = glm::vec3(0);

	vec.x = std::stof(split[0]);
	vec.y = std::stof(split[1]);
	vec.z = std::stof(split[2]);

	return vec;
}