#include "Light.h"
#include "Renderer.h"

std::vector<DirectionalLight*> Light::directionalLights;
std::vector<PointLight*> Light::pointLights;
std::vector<SpotLight*> Light::spotLights;

double Light::lastDealtTime = 0;
bool Light::UpdateLighting = false;

Light::Light()
{
}


Light::~Light()
{
}

void Light::RenderUIEditor() {

	glm::vec3 lastAmbient = ambient;
	glm::vec3 lastDiffuse = diffuse;

	ImGui::ColorEdit3("ambient", glm::value_ptr(ambient));
	ImGui::ColorEdit3("diffuse", glm::value_ptr(diffuse));

	if (lastDiffuse != diffuse || lastAmbient != ambient) {
		UpdateLighting = true;
		std::cout << "Update Lighting" << std::endl;
	}
}

void Light::Update(double deltaTime) {

	if (UpdateLighting) {

		Renderer::CurrentShaderProgram->use();
		UpdateLighting = false;
	}
}

void Light::RenderUIEditorLightAttenuation() {

	ImGui::DragFloat("Constant", &constant, 0.01f);
	ImGui::DragFloat("Linear", &linear, 0.01f);
	ImGui::DragFloat("Quadratic", &quadratic, 0.01f);
	
	UpdateLighting = true;
}