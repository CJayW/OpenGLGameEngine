#pragma once
#include "Light.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class DirectionalLight :
	public Light
{
public:
	static std::string name;

	DirectionalLight();
	DirectionalLight(std::string params);
	~DirectionalLight();

	void Start() override;

	void UpdateLight() override;


	//Editor
	void RenderUIEditor() override;
	glm::quat lastRot;

	int findLightPos() {
		for (unsigned int i = 0; i < directionalLights.size(); i++) {
			if (directionalLights[i] != nullptr && directionalLights[i]->ID == ID) {
				return i;
			}
		}
		return -1;
	}
};