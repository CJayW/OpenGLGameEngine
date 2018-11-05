#include "SpotLight.h"

#include "LevelFileManager.h"
#include "Shader.h"

#include "Transform.h"

#include "IconRenderer.h"

std::string SpotLight::name = "SpotLight";

SpotLight::SpotLight() {

	diffuse = glm::vec3(0.8f);

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	float width = 15;
	float blur = 0.17f;

	DisplayName = name;
}

SpotLight::SpotLight(std::string params) {

	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');

	diffuse = LevelFileManager::stringToVec3(splitParams[0]);

	constant = std::stof(splitParams[1]);
	linear = std::stof(splitParams[2]);
	quadratic = std::stof(splitParams[3]);

	width = std::stof(splitParams[4]);
	blur = std::stof(splitParams[5]);

	DisplayName = name;

}

SpotLight::~SpotLight() {
	UpdateLight();
	spotLights[findLightPos()] = nullptr;
}

std::string SpotLight::ToSaveString() {
	std::string str = "";
	str += name;
	str += "(";
	str += LevelFileManager::vec3ToSaveString(diffuse);
	str += ",";
	str += attenuationToString();
	str += ",";
	str += std::to_string(width);
	str += ",";
	str += std::to_string(blur );

	return str;
}

void SpotLight::Start() {
	spotLights[getFirstEmpty(spotLights)] = this;

	IconRenderer* icon = gameObject->addComponent<IconRenderer>("spot_icon.jpg");
}

void SpotLight::UpdateLight() {
	unsigned int index = findLightPos();

	for (auto shader : Shader::Shaders) {
		if (shader->useLightData) {
			shader->SpotLightsToUpdate.push_back(index);
		}
	}
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