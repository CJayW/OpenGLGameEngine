#pragma once
#include "Component.h"
#include <vector>

class DirectionalLight;
class PointLight;
class SpotLight;

class Light :
	public Component
{
public:
	Light();
	virtual ~Light();

	void Update(double deltaTime) override;

	//Lighting Vectors
	static std::vector<DirectionalLight*> directionalLights;
	static std::vector<PointLight*> pointLights;
	static std::vector<SpotLight*> spotLights;

	
	//Lighting Variables
	glm::vec3 ambient;
	glm::vec3 diffuse;

	float constant;
	float linear;
	float quadratic;

	static bool UpdateLighting;

	//Editor
	void RenderUIEditorLightAttenuation();
	void RenderUIEditor() override;
};