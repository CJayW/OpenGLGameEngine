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

	//Editor
	void RenderUIEditor() override;
	glm::quat lastRot;
};