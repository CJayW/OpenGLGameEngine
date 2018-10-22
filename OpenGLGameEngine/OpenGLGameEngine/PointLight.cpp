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

//vec3 ambient, vec3 diffuse, float constant, float linear, float quadratic

PointLight::PointLight(std::string params) {
	pointLights.push_back(this);

	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');

	ambient = LevelFileManager::stringToVec3(splitParams[0]);
	diffuse = LevelFileManager::stringToVec3(splitParams[1]);
	
	constant = std::stof(splitParams[2]);
	linear = std::stof(splitParams[3]);
	quadratic = std::stof(splitParams[4]);

	DisplayName = name;

	//TODO implament a range to this
	//http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
}

void PointLight::Start() {
	gameObject->addComponent<IconRenderer>("pointLightIcon.jpg");

}

PointLight::~PointLight() {
}

void PointLight::RenderUIEditor() {
	Light::RenderUIEditor();
	RenderUIEditorLightAttenuation();
}