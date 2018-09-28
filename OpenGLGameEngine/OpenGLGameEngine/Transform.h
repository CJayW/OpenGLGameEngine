#pragma once
#include "Component.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
class Transform : public Component{
public:
	Transform();
	Transform(std::string message);
	~Transform();

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	void rotate(glm::vec3 euler);
};