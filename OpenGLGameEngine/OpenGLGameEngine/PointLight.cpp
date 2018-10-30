#include "PointLight.h"

#include "LevelFileManager.h"

std::string PointLight::name = "PointLight";

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "IconRenderer.h"

#include "EditorDebug.h"

#include "Transform.h"

PointLight::PointLight() {
	pointLights[getFirstEmpty(pointLights)] = this;

	DisplayName = name;
}

PointLight::PointLight(std::string params) {
	pointLights[getFirstEmpty(pointLights)] = this;

	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');
	ambient = LevelFileManager::stringToVec3(splitParams[0]);
	diffuse = LevelFileManager::stringToVec3(splitParams[1]);
	
	constant = std::stof(splitParams[2]);
	linear = std::stof(splitParams[3]);
	quadratic = std::stof(splitParams[4]);

	DisplayName = name;

	//http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
}

PointLight::~PointLight() {
	UpdateLight();
	pointLights[findLightPos()] = nullptr;
}

void PointLight::Start() {
	UpdateLight();
	gameObject->addComponent<IconRenderer>("pointLightIcon.jpg");
}

void PointLight::UpdateLight() {
	unsigned int index = findLightPos();
	
	for (auto shader : Shader::Shaders) {
		if (shader->useLightData) {
			shader->PointLightsToUpdate.push_back(index);
		}
	}
}

void PointLight::RenderUIEditor() {
	Light::RenderUIEditor();
	RenderUIEditorLightAttenuation();
	bool changed = false;

	if (transform->getPosition() != lastPos) {
		lastPos = transform->getPosition();
		UpdateLight();
	}
}