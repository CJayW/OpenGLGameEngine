#pragma once
#include <iostream>
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
	
	void UpdateLight() override;

	int findLightPos() {
		for (unsigned int i = 0; i < pointLights.size(); i++) {
			if (pointLights[i] != nullptr && pointLights[i]->ID == ID) {
				return i;
			}
		}
		return -1;
	}


	//Editor
	void RenderUIEditor() override;
	glm::vec3 lastPos;
};