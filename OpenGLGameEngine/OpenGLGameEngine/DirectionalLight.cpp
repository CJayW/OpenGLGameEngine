#include "DirectionalLight.h"
#include <string>
#include "LevelFileManager.h"
#include "Transform.h"
#include "IconRenderer.h"

#include "EditorDebug.h"
std::string DirectionalLight::name = "DirectionalLight";


DirectionalLight::DirectionalLight()
{
	directionalLights[getFirstEmpty(directionalLights)] = this;

	ambient = glm::vec3(0.1f);
	diffuse = glm::vec3(0.8f);
	
	DisplayName = name;
}

DirectionalLight::DirectionalLight(std::string params) {
	directionalLights[getFirstEmpty(directionalLights)] = this;

	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');

	ambient = LevelFileManager::stringToVec3(splitParams[0]);
	diffuse = LevelFileManager::stringToVec3(splitParams[1]);

	DisplayName = name;

}

DirectionalLight::~DirectionalLight() {
	UpdateLight();
	directionalLights[findLightPos()] = nullptr;
}

void DirectionalLight::Start() {
	gameObject->addComponent<IconRenderer>("directional_icon.jpg");
}

void DirectionalLight::UpdateLight() {
	unsigned int index = findLightPos();
	
	EditorDebug::Log(std::to_string(index));

	for (auto shader : Shader::Shaders) {
		if (shader->useLightData) {
			shader->DirLightsToUpdate.push_back(index);
		}
	}
}

void DirectionalLight::RenderUIEditor() {
	Light::RenderUIEditor();

	if (lastRot != transform->rotation) {
		UpdateLight();
		lastRot = transform->rotation;
	}
}