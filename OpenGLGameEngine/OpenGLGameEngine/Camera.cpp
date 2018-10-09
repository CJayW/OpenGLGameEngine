#include "Camera.h"
#include "Game.h"

#include <glm\gtc\type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Transform.h"

glm::mat4 Camera::projection;
glm::mat4 Camera::viewMatrix;

std::vector<Renderer*> Camera::Renderers;
float Camera::FOV = 60;

std::string Camera::name = "Camera";

Camera::Camera()
{
}

Camera::Camera(std::string params) {
	FOV = std::stof(params);
}

Camera::~Camera()
{	
}

void Camera::Start() {
	UpdateCameraView();
	UpdateCameraProjection();
}

void Camera::Update(double deltaTime) {
	UpdateCameraView();
}

void Camera::UpdateCameraProjection() {
	float ratio = ((float)Game::width / (float)Game::height);
	projection = glm::perspective(glm::radians(FOV), ratio, 0.1f, 100.0f);
	
	for (auto renderer : Renderers) {
		renderer->UpdateCameraProjection();
	}
}

void Camera::UpdateCameraView() {

	glm::vec3 cameraPos = transform->position;

	glm::vec3 cameraFront = transform->rotation * glm::vec3(1, 0, 0);

	glm::vec3 cameraUp = transform->rotation * glm::vec3(0, 1, 0);

	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	for (auto renderer : Renderers) {
		renderer->UpdateCameraView();
	}
}

void Camera::AddRenderer(Renderer* newRenderer) {
	Camera::Renderers.push_back(newRenderer);
	newRenderer->UpdateCameraView();
	newRenderer->UpdateCameraProjection();
}