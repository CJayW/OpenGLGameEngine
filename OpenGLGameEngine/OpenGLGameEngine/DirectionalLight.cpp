#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	directionalLights.push_back(this);
}

DirectionalLight::DirectionalLight(std::string params) {
	directionalLights.push_back(this);
	ambient = glm::vec3(0.1f);
	diffuse = glm::vec3(0.8f);
}

DirectionalLight::~DirectionalLight()
{
}