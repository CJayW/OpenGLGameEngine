#include "DirectionalLight.h"
#include <string>
#include "LevelFileManager.h"
#include "Transform.h"
#include "IconRenderer.h"

std::string DirectionalLight::name = "DirectionalLight";


DirectionalLight::DirectionalLight()
{
	index = directionalLights.size();
	directionalLights.push_back(this);

	ambient = glm::vec3(0.1f);
	diffuse = glm::vec3(0.8f);
	
	DisplayName = name;
}

DirectionalLight::DirectionalLight(std::string params) {
	index = directionalLights.size();
	directionalLights.push_back(this);
	
	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');

	ambient = LevelFileManager::stringToVec3(splitParams[0]);
	diffuse = LevelFileManager::stringToVec3(splitParams[1]);

	DisplayName = name;
}

void DirectionalLight::Start() {
	gameObject->addComponent<IconRenderer>("directional_icon.jpg");

}

DirectionalLight::~DirectionalLight() {
	for (int i = 0; i < directionalLights.size(); i++) {
		if (directionalLights[i]->gameObject == gameObject) {
			directionalLights.erase(directionalLights.begin() + i);
			return;
		}
	}
	std::cout << "Error Finding DirectionalLight" << std::endl;
}

void DirectionalLight::RenderUIEditor() {
	Light::RenderUIEditor();

	if (lastRot != transform->rotation) {
		UpdateLighting = true;
		lastRot = transform->rotation;
	}
}