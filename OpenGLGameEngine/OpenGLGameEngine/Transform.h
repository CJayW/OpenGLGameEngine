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

	glm::vec3 localPos;
	glm::quat rotation;
	glm::vec3 scale;

	void rotate(glm::vec3 euler);
	glm::mat4 GetModelMat();
	glm::vec3 getPosition();
	glm::quat getRotation();
	//Editor
	void OpenUIEditor() override;

	void RenderUIEditor() override;

	glm::vec3 EditorRotation;



};