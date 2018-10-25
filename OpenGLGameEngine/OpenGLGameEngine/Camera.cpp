#include "Camera.h"
#include "Game.h"

#include <glm\gtc\type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Transform.h"

#include "Renderer.h"

glm::mat4 Camera::projection;
glm::mat4 Camera::viewMatrix;
glm::vec3 Camera::cameraPos;

float Camera::FOV = 60;

std::string Camera::name = "Camera";

Camera::Camera()
{
	DisplayName = name;
}

Camera::Camera(std::string params) {
	FOV = std::stof(params);
	DisplayName = name;
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

	cameraPos = transform->position;
}

void Camera::UpdateCameraProjection() {
	float ratio = ((float)Game::width / (float)Game::height);
	projection = glm::perspective(glm::radians(FOV), ratio, 0.1f, 100.0f);
	

	for (auto renderer : Renderer::Renderers) {
		renderer->UpdateCameraProjection();
	}
}

void Camera::UpdateCameraView() {
	glm::vec3 cameraPos = transform->position;

	glm::vec3 cameraFront = transform->rotation * glm::vec3(1, 0, 0);

	glm::vec3 cameraUp = transform->rotation * glm::vec3(0, 1, 0);

	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	Renderer::CurrentShaderProgram->setMat4("view", viewMatrix);
}

void Camera::RenderUIEditor() {
	float lastFOV = FOV;
	
	ImGui::DragFloat("FOV", &FOV, 0.1f);

	if (lastFOV != FOV)
		UpdateCameraProjection();
}