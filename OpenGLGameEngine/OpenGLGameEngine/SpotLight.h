#pragma once
#include "Light.h"

#include <glm/glm.hpp>
#include <string>

class SpotLight : public Light {
public:
	static std::string name;

	SpotLight();
	SpotLight(std::string params);
	~SpotLight();

	float constant;
	float linear;
	float quadratic;

	float width;
	float blur;

	void RenderUIEditor() override;

};