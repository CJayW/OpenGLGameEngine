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

	//Lighting Vectors
	static std::array<DirectionalLight*, maxLightCount> directionalLights;
	static std::array<PointLight*, maxLightCount> pointLights;
	static std::array<SpotLight*, maxLightCount> spotLights;
	
	//Lighting Variables
	glm::vec3 ambient;
	glm::vec3 diffuse;

	float constant;
	float linear;
	float quadratic;

		virtual void UpdateLight() {};

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