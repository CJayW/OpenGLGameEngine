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

	diffuse = glm::vec3(0.8f);
	
	DisplayName = name;
}

DirectionalLight::DirectionalLight(std::string params) {
	directionalLights[getFirstEmpty(directionalLights)] = this;

	diffuse = LevelFileManager::stringToVec3(params);

	DisplayName = name;

}

DirectionalLight::~DirectionalLight() {
	UpdateLight();
	directionalLights[findLightPos()] = nullptr;
}

std::string DirectionalLight::ToSaveString() {
	std::string str = "";
	str += name;
	str += "(";
	
	str += LevelFileManager::vec3ToSaveString(diffuse);

	return str;
}

void DirectionalLight::Start() {
	IconRenderer* icon = gameObject->addComponent<IconRenderer>("directional_icon.jpg");
	icon->inSaveFile = false;

}

void DirectionalLight::UpdateLight() {
	unsigned int index = findLightPos();
	
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