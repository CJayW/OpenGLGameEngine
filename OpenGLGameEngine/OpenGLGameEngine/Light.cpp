#include "Light.h"
#include "Renderer.h"

std::array<DirectionalLight*, maxLightCount> Light::directionalLights;
std::array<PointLight*, maxLightCount> Light::pointLights;
std::array<SpotLight*, maxLightCount> Light::spotLights;

//TODO	either make each light store the index that its at so that it doesnt need to find itself each time it changes
//		or sort the arrays to remove empty spaces

Light::Light()
{
}


Light::~Light()
{
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

	changed = ImGui::ColorEdit3((std::string("ambient") + idTag).c_str(), glm::value_ptr(ambient));
	changed = ImGui::ColorEdit3((std::string("diffuse") + idTag).c_str(), glm::value_ptr(diffuse)) ? true : changed;

	if (changed)
		UpdateLight();
}