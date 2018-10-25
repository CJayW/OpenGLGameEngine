#pragma once

#include <string>
#include <glm/glm.hpp>

#include "Light.h"

class PointLight : public Light {
public:

	static std::string name;

	PointLight();
	PointLight(std::string params);
	~PointLight();

	void Start() override;
	
	//Editor
	void RenderUIEditor() override;
};