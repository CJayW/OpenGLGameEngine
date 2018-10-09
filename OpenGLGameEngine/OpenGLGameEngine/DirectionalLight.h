#pragma once
#include "Light.h"

#include <glm/glm.hpp>

class DirectionalLight :
	public Light
{
public:

	static std::string name;

	DirectionalLight();
	DirectionalLight(std::string params);
	~DirectionalLight();

	glm::vec3 ambient;
	glm::vec3 diffuse;
};