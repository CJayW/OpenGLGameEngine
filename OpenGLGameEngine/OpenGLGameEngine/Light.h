#pragma once
#include "Component.h"
#include <array>

#include "EditorDebug.h"

//#include "PointLight.h"

#define maxLightCount 10

class DirectionalLight;
class PointLight;
class SpotLight;

class Light :
	public Component
{
public:
	Light();
	virtual ~Light();

	std::string attenuationToString();

	//Lighting Vectors
	static std::array<DirectionalLight*, maxLightCount> directionalLights;
	static std::array<PointLight*, maxLightCount> pointLights;
	static std::array<SpotLight*, maxLightCount> spotLights;
	
	static glm::vec3 Ambient;
	static glm::vec3 ClearColour;

	//Lighting Variables
	glm::vec3 diffuse;

	float constant;
	float linear;
	float quadratic;

	virtual void UpdateLight() {};

	static void UpdateClearColour(glm::vec3 newColour = ClearColour);
	static void UpdateAmbient(glm::vec3 newColour = Ambient);

	//Editor
	void RenderUIEditorLightAttenuation();
	void RenderUIEditor() override;

	template<class type>
	int getFirstEmpty(type arr) {
		for (unsigned int i = 0; i < arr.size(); i++) {
			if (arr[i] == nullptr) {
				return i;
			}
		}
		return -1;
	}
};