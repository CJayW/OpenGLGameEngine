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

	static std::vector<DirectionalLight*> directionalLights;
	static std::vector<PointLight*> pointLights;
	static std::vector<SpotLight*> spotLights;

	int index;

	glm::vec3 ambient;
	glm::vec3 diffuse;

	float constant;
	float linear;
	float quadratic;

	void Update(double deltaTime) override;

	void RenderUIEditor() override;

	static double lastDealtTime;
	static bool UpdateLighting;

	void RenderUIEditorLightAttenuation();

	bool find;
};