#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Transform.h"
#include "Renderer.h"

#include <vector>

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void Start() override;

	static void UpdateCameraProjection();

	static void UpdateCameraView();

	static void AddRenderer(Renderer* newRenderer);

	float FOV = 45;

	static glm::mat4 projection;
	static glm::mat4 viewMatrix;

	static std::vector<Renderer*> Renderers;
};