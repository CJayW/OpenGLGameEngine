#pragma once
#include "Light.h"

#include <glm/glm.hpp>

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(std::string params);
	~DirectionalLight();

	glm::vec3 ambient;
	glm::vec3 diffuse;
};