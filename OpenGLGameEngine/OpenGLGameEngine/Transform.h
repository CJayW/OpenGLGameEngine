#pragma once
#include "Component.h"
#include <string>
#include <glm/vec3.hpp>

class Transform : public Component{
public:
	Transform();
	Transform(std::string message);
	~Transform();

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

