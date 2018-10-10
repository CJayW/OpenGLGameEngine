#include "DirectionalLight.h"
#include <string>
#include "LevelFileManager.h"

std::string DirectionalLight::name = "DirectionalLight";


DirectionalLight::DirectionalLight()
{
	directionalLights.push_back(this);

	ambient = glm::vec3(0.1f);
	diffuse = glm::vec3(0.8f);
}

//vec3 ambient, vec3 diffuse

DirectionalLight::DirectionalLight(std::string params) {
	directionalLights.push_back(this);

	
	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');

	ambient = LevelFileManager::stringToVec3(splitParams[0]);
	diffuse = LevelFileManager::stringToVec3(splitParams[1]);
	

}

DirectionalLight::~DirectionalLight()
{
}