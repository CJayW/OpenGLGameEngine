#include "Light.h"
#include "Renderer.h"

std::vector<DirectionalLight*> Light::directionalLights;
std::vector<PointLight*> Light::pointLights;
std::vector<SpotLight*> Light::spotLights;

bool Light::UpdateLighting = false;

Light::Light()
{
}


Light::~Light()
{
}

void Light::Update(double deltaTime) {

	if (UpdateLighting) {

		Renderer::CurrentShaderProgram->use();
		UpdateLighting = false;
	}
}

void Light::RenderUIEditorLightAttenuation() {
	std::string idTag = std::string("##") + std::to_string(ID);

	ImGui::DragFloat((std::string("Constant" ) + idTag).c_str(), &constant, 0.01f);
	ImGui::DragFloat((std::string("Linear"   ) + idTag).c_str(), &linear, 0.01f);
	ImGui::DragFloat((std::string("Quadratic") + idTag).c_str(), &quadratic, 0.01f);

	UpdateLighting = true;
}

void Light::RenderUIEditor() {

	std::string idTag = std::string("##") + std::to_string(ID);

	glm::vec3 lastAmbient = ambient;
	glm::vec3 lastDiffuse = diffuse;

	ImGui::ColorEdit3((std::string("ambient") + idTag).c_str(), glm::value_ptr(ambient));
	ImGui::ColorEdit3((std::string("diffuse") + idTag).c_str(), glm::value_ptr(diffuse));

	if (lastDiffuse != diffuse || lastAmbient != ambient) {
		UpdateLighting = true;
		std::cout << "Update Lighting" << std::endl;
	}
}