#include "SpotLight.h"

#include "LevelFileManager.h"


std::string SpotLight::name = "SpotLight";

SpotLight::SpotLight() {
	spotLights.push_back(this);

	ambient = glm::vec3(0.05f);
	diffuse = glm::vec3(0.8f);

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	float width = 15;
	float blur = 0.17;

	DisplayName = name;

}

SpotLight::SpotLight(std::string params) {
	spotLights.push_back(this);

	ambient = glm::vec3(0);
	diffuse = glm::vec3(0.8f);

	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;

	width = 15;
	blur = 0.17;

	DisplayName = name;

}

SpotLight::~SpotLight() {
}

void SpotLight::RenderUIEditor() {
	Light::RenderUIEditor();
	RenderUIEditorLightAttenuation();

	//TODO use this at some point

}