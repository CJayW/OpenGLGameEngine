#include "Light.h"
#include "Renderer.h"

std::array<DirectionalLight*, maxLightCount> Light::directionalLights;
std::array<PointLight*, maxLightCount> Light::pointLights;
std::array<SpotLight*, maxLightCount> Light::spotLights;

glm::vec3 Light::Ambient = glm::vec3(0);
glm::vec3 Light::ClearColour = glm::vec3(0);

Light::Light()
{
}


Light::~Light()
{
}

std::string Light::attenuationToString() {
	std::string str = "";

	str += std::to_string(constant);
	str += ",";
	str += std::to_string(linear);
	str += ",";	
	str += std::to_string(quadratic);

	return str;
}

void Light::UpdateClearColour(glm::vec3 newColour) {
	glClearColor(newColour.r, newColour.g, newColour.b, 1);
	ClearColour = newColour;
}

void Light::UpdateAmbient(glm::vec3 newColour) {
	for (auto shader : Shader::Shaders) {
		if(shader->useLightData)
			shader->UpdateAmbient = true;
	}
	Ambient = newColour;
}

void Light::RenderUIEditorLightAttenuation() {
	std::string idTag = std::string("##") + std::to_string(ID);

	bool changed = false;

	changed = ImGui::DragFloat((std::string("Constant" ) + idTag).c_str(), &constant, 0.01f);
	changed = ImGui::DragFloat((std::string("Linear"   ) + idTag).c_str(), &linear, 0.01f   ) ? true : changed;
	changed = ImGui::DragFloat((std::string("Quadratic") + idTag).c_str(), &quadratic, 0.01f) ? true : changed;

	if(changed)
		UpdateLight();
}

void Light::RenderUIEditor() {

	std::string idTag = std::string("##") + std::to_string(ID);

	bool changed = false;

	changed = ImGui::ColorEdit3((std::string("diffuse") + idTag).c_str(), glm::value_ptr(diffuse)) ? true : changed;

	if (changed)
		UpdateLight();
}