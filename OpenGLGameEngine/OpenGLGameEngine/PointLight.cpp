#include "PointLight.h"

#include "LevelFileManager.h"

std::string PointLight::name = "PointLight";

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "IconRenderer.h"

PointLight::PointLight() {
	pointLights.push_back(this);

	DisplayName = name;
}

PointLight::PointLight(std::string params) {
	pointLights.push_back(this);

	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');
	ambient = LevelFileManager::stringToVec3(splitParams[0]);
	diffuse = LevelFileManager::stringToVec3(splitParams[1]);
	
	constant = std::stof(splitParams[2]);
	linear = std::stof(splitParams[3]);
	quadratic = std::stof(splitParams[4]);

	DisplayName = name;

	//http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
}

void PointLight::Start() {
	gameObject->addComponent<IconRenderer>("pointLightIcon.jpg");

}

PointLight::~PointLight() {
	for (int i = 0; (size_t)i < pointLights.size(); i++) {
		if (pointLights[i]->gameObject == gameObject) {
			pointLights.erase(pointLights.begin() + i);
			return;
		}
	}

	std::cout << "Error Finding PointLight" << std::endl;
	//TODO, Use an ID for this instead of comparing objects
}

void PointLight::RenderUIEditor() {
	Light::RenderUIEditor();
	RenderUIEditorLightAttenuation();
}