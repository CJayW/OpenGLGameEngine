#pragma once
#include "Light.h"

#include <glm/glm.hpp>
#include <string>

class SpotLight : public Light {
public:
	SpotLight();
	SpotLight(std::string params);
	~SpotLight();

	glm::vec3 ambient;
	glm::vec3 diffuse;

	float constant;
	float linear;
	float quadratic;

	float width;
	float blur;
};