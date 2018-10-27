#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class EditorCamera {
public:
	EditorCamera();
	~EditorCamera();

	void UpdateCameraView();

	void Update();

	glm::vec3 Pos;
	glm::quat Rot;
	void rotate(glm::vec3 euler);
};

