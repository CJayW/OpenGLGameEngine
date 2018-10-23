#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <vector>

class Camera : public Component
{
public:

	static std::string name;

	Camera();
	Camera(std::string params);
	~Camera();

	void Start() override;
	void Update(double deltaTime) override;

	static void UpdateCameraProjection();
	void UpdateCameraView();

	static glm::mat4 projection;
	static glm::mat4 viewMatrix;

	void RenderUIEditor() override;

	static glm::vec3 cameraPos;

private:
	static float FOV;
};