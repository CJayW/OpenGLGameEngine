#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "Game.h"
glm::mat4 Camera::projection;
glm::mat4 Camera::viewMatrix;

std::vector<Renderer*> Camera::Renderers;

Camera::Camera()
{
}

Camera::~Camera()
{	
}

void Camera::Start() {
	transform->position.z += 3;
}

void Camera::UpdateCameraProjection() {
	float ratio = ((float)Game::width / (float)Game::height);
	projection = glm::perspective(glm::radians(60.0f), ratio, 0.1f, 100.0f);
	
	for (auto renderer : Renderers) {
		renderer->UpdateCameraProjection();
	}
}

void Camera::UpdateCameraView() {
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	for (auto renderer : Renderers) {
		renderer->UpdateCameraView();
	}
}

void Camera::AddRenderer(Renderer* newRenderer) {
	Camera::Renderers.push_back(newRenderer);
	newRenderer->UpdateCameraView();
	newRenderer->UpdateCameraProjection();
	std::cout << "here" << std::endl;
}