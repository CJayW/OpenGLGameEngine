#include "SpotLight.h"

#include "LevelFileManager.h"
#include "Shader.h"

#include "Transform.h"

#include "IconRenderer.h"

std::string SpotLight::name = "SpotLight";

SpotLight::SpotLight() {

	ambient = glm::vec3(0.05f);
	diffuse = glm::vec3(0.8f);

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	float width = 15;
	float blur = 0.17f;

	DisplayName = name;
}

SpotLight::SpotLight(std::string params) {

	ambient = glm::vec3(0);
	diffuse = glm::vec3(0.8f);

	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;

	width = 15;
	blur = 0.17f;

	DisplayName = name;

	//TODO this
}

void SpotLight::Start() {
	spotLights[getFirstEmpty(spotLights)] = this;
	spotLights[getFirstEmpty(spotLights)] = this;

	gameObject->addComponent<IconRenderer>("spot_icon.jpg");

}

void SpotLight::UpdateLight() {
	unsigned int index = findLightPos();

	for (auto shader : Shader::Shaders) {
		if (shader->useLightData) {
			shader->SpotLightsToUpdate.push_back(index);
		}
	}
}

SpotLight::~SpotLight() {
	UpdateLight();
	spotLights[findLightPos()] = nullptr;
}

void SpotLight::RenderUIEditor() {
	Light::RenderUIEditor();
	RenderUIEditorLightAttenuation();

	bool changed = false;

	if(transform->getPosition() != lastPos){
		lastPos = transform->getPosition();
		changed = true;
	}
	
	if (transform->getRotation() != lastRot) {
		lastRot = transform->getRotation();
		changed = true;
	}
	
	changed = ImGui::DragFloat("Width", &width, 0.1f) ? true : changed;
	changed = ImGui::SliderFloat("blur", &blur, 0.0f, 1.0f) ? true : changed;

	if (changed) {
		UpdateLight();
	}
}