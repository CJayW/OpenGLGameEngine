#pragma once

#include <string>
#include <glm/glm.hpp>

#include "Light.h"

class PointLight : public Light {
public:
	PointLight();
	PointLight(std::string params);
	~PointLight();

	glm::vec3 ambient;
	glm::vec3 diffuse;

	float constant;
	float linear;
	float quadratic;

};