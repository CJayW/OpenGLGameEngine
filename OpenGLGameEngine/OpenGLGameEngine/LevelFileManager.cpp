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

#include "EditorDebug.h"

#include "Shader.h"

LevelFileManager::LevelFileManager() {
}

LevelFileManager::~LevelFileManager() {
}

void LevelFileManager::loadLevel() {

	std::string file;

	std::ifstream ip("Resources/Levels/Level2.txt");
	//while there are more lines
	while (ip.good()) {
		std::getline(ip, file);
		
		if (file.find("return") == 0) {
			ip.close();
			return;
		} else if (file[0] == '#') {
			std::vector<std::string> params = splitBy(file, ':');
			
			if (params.size() < 2)
				continue;

			if (params[0] == "#Ambient") {
				Light::Ambient = stringToVec3(params[1]);

				Light::UpdateAmbient();
			} else if (params[0] == "#ClearColour") {
				Light::ClearColour = stringToVec3(params[1]);

				Light::UpdateClearColour();
			}

		} else if(file != "" && file.find("//") != 0) {

			int childIndex = 0;

			while (file[0] == '-') {
				childIndex++;
				file = removeFirstChar(file);
			}

			GameObject* parent = nullptr;

			for (int i = 0; i < childIndex; i++) {
				if (parent == nullptr) {
					parent = Game::GameObjects[Game::GameObjects.size() -1];
				} else {
					parent = parent->children[parent->children.size() - 1];
				}
			}

			GameObject* obj;
			if (parent != nullptr) {
				obj = GameObjectManager::Instantiate(parent);
			} else {
				obj = GameObjectManager::Instantiate();
			}

			for (auto componentString : splitBy(file, ':')) {
				std::vector<std::string> componentInfo = splitBy(componentString, '(');

				//sets the name of the object
				if (componentInfo.size() < 2) {
					obj->Name = componentInfo[0];
					continue;
				}
				std::vector<std::string> params;

				std::string componentName = componentInfo[0];

				if (componentName == "Translate") {
					//Translate
					obj->transform->localPos = stringToVec3(componentInfo[1]);;
				} else if (componentName == "Rotate") {
					//Rotate

					glm::vec3 rot = stringToVec3(componentInfo[1]);

					rot /= 180 / glm::pi<float>();

					obj->transform->rotation = glm::quat(rot);
				} else if (componentName == "Scale") {
					//Scale
					obj->transform->scale = stringToVec3(componentInfo[1]);
				} else if (componentName == MeshRenderer::name) {
					//MeshRenderer
					obj->addComponent<MeshRenderer>(componentInfo[1]);
				} else if (componentName == Camera::name) {
					//Camera
					Game::camera = obj->addComponent<Camera>(componentInfo[1]);
				} else if (componentName == CameraMovement::name) {
					//CameraMovement
					obj->addComponent<CameraMovement>(componentInfo[1]);
				} else if (componentName == TestMove::name) {
					//TestMove
					obj->addComponent<TestMove>(componentInfo[1]);
				} else if (componentName == DirectionalLight::name) {
					//DirectionalLight
					obj->addComponent<DirectionalLight>(componentInfo[1]);
				} else if (componentName == PointLight::name) {
					//PointLight
					obj->addComponent<PointLight>(componentInfo[1]);
				} else if (componentName == SpotLight::name) {
					//spotLight
					obj->addComponent<SpotLight>(componentInfo[1]);
				} else if (componentName == Rigidbody::name) {
					//ComponentTemplate
					obj->addComponent<Rigidbody>(componentInfo[1]);
				} else if (componentName == IconRenderer::name) {
					//Icon Renderer
					obj->addComponent<IconRenderer>(componentInfo[1]);
				}
				
				//TODO #Define CheckComp(type)

				/*
				else if (componentName == ComponentTemplate::name) {
					//ComponentTemplate
					obj->addComponent<ComponentTemplate>(componentInfo[1]);
				}
				*/
				else {

					EditorDebug::ErrorLog("Failed To Find Component: '" + componentName + "'");
				}
			}
		}
	}
	ip.close();
}


#define Write() ip.write(file.c_str(), file.size()); file = ""
#define addLine(newStr) file += newStr; file += "\n";
bool LevelFileManager::saveLevel() {
	std::ofstream ip("Resources/Levels/Level2.txt");

	std::string file = "";
	
	addLine("#Ambient:" + vec3ToSaveString(Light::Ambient));
	addLine("#ClearColour:" + vec3ToSaveString(Light::ClearColour));
	
	std::string str = "";

	for (auto obj : Game::GameObjects) {
		//TODO add parenting to this

		#pragma region 
		file += obj->Name;
		file += ':';
		file += "Translate(";
		file += vec3ToSaveString(obj->transform->localPos);
		file += ":Rotate(";

		glm::vec3 rot = glm::eulerAngles(obj->transform->rotation);
		rot *= 180 / glm::pi<float>();
		file += vec3ToSaveString(rot);

		file += ":Scale(";
		file += vec3ToSaveString(obj->transform->scale);
		
		#pragma endregion Transform

		unsigned int total = obj->components.size();

		for (int i = 1; i < total; i++) {
			file += ":";

			file += obj->components[i]->ToSaveString();
		}

		file += "\n";
	}

	Write();

	ip.close();
	return true;
}

std::string LevelFileManager::removeFirstChar(std::string string) {
	std::string str = "";
	
	for (int i = 0; i < string.size() - 2; i++) {
		str += string[i + 1];
	}

	return str;
}

std::string LevelFileManager::vec3ToSaveString(glm::vec3 vec) {

	std::string str = "";
	str += std::to_string(vec.x);
	str += "~ ";
	str += std::to_string(vec.y);
	str += "~ ";
	str += std::to_string(vec.z);

	return str;
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
	std::vector<std::string> split = splitBy(str, '~');

	if (split.size() < 3) {
		return glm::vec3(0);
	}

	glm::vec3 vec = glm::vec3(0);

	vec.x = std::stof(split[0]);
	vec.y = std::stof(split[1]);
	vec.z = std::stof(split[2]);

	return vec;
}