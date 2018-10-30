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

	std::string ToSaveString() override;

	void Start() override;

	float width;
	float blur;

	void UpdateLight() override;

	int findLightPos() {
		for (unsigned int i = 0; i < spotLights.size(); i++) {
			if (spotLights[i] != nullptr && spotLights[i]->ID == ID) {
				return i;
			}
		}
		return -1;
	}

	//Editor
	void RenderUIEditor() override;

	glm::quat lastRot;
	glm::vec3 lastPos;

};