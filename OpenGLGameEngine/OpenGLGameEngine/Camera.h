#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Renderer.h"

#include <vector>

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void Start() override;

	void Update(double deltaTime) override;

	static void UpdateCameraProjection();

	void UpdateCameraView();

	static void AddRenderer(Renderer* newRenderer);

	static glm::mat4 projection;
	static glm::mat4 viewMatrix;

private:
	static float FOV;

	static std::vector<Renderer*> Renderers;
};