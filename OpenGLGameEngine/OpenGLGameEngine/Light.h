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
	~Light();

	static std::vector<DirectionalLight*> directionalLights;
	static std::vector<PointLight*> pointLights;
	static std::vector<SpotLight*> spotLights;

	glm::vec3 ambient;
	glm::vec3 diffuse;

	float constant;
	float linear;
	float quadratic;

	void RenderUIEditor() override;

	void Update(double deltaTime) override;

	static double lastDealtTime;
	static bool UpdateLighting;

	void RenderUIEditorLightAttenuation();


};