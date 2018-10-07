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
};