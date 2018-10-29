#include "DirectionalLight.h"
#include <string>
#include "LevelFileManager.h"
#include "Transform.h"
#include "IconRenderer.h"

#include "EditorDebug.h"
std::string DirectionalLight::name = "DirectionalLight";


DirectionalLight::DirectionalLight()
{
	directionalLights.push_back(this);

	ambient = glm::vec3(0.1f);
	diffuse = glm::vec3(0.8f);
	
	DisplayName = name;
}

DirectionalLight::DirectionalLight(std::string params) {
	directionalLights.push_back(this);
	
	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');

	ambient = LevelFileManager::stringToVec3(splitParams[0]);
	diffuse = LevelFileManager::stringToVec3(splitParams[1]);

	DisplayName = name;
}

DirectionalLight::~DirectionalLight() {
	for (int i = 0; (size_t)i < directionalLights.size(); i++) {
		if (directionalLights[i]->ID == ID) {
			directionalLights.erase(directionalLights.begin() + i);
			return;
		}
	}
	EditorDebug::Log("Error Finding DirectionalLight", LogLevelError);
}

void DirectionalLight::Start() {
	gameObject->addComponent<IconRenderer>("directional_icon.jpg");

}

void DirectionalLight::RenderUIEditor() {
	Light::RenderUIEditor();

	if (lastRot != transform->rotation) {
		UpdateLighting = true;
		lastRot = transform->rotation;
	}
}