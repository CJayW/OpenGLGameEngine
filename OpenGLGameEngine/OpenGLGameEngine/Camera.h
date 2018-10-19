#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Renderer.h"

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

	static void AddRenderer(Renderer* newRenderer);
	static void UpdateCameraProjection();
	void UpdateCameraView();

	static glm::mat4 projection;
	static glm::mat4 viewMatrix;

	void RenderUIEditor() override;

private:
	static float FOV;

	static std::vector<Renderer*> Renderers;
};