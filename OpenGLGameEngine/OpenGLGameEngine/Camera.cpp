#include "Camera.h"
#include "Game.h"

#include <glm\gtc\type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Transform.h"

#include "Renderer.h"
#include "IconRenderer.h"

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
	Game::camera = NULL;
}

void Camera::Start() {
	UpdateCameraView();
	UpdateCameraProjection();
	gameObject->addComponent<IconRenderer>("CameraIcon.jpg");
}

void Camera::Update(double deltaTime) {
}

void Camera::UpdateCameraProjection() {
	float ratio = ((float)Game::width / (float)Game::height);
	projection = glm::perspective(glm::radians(FOV), ratio, 0.1f, 100.0f);
	
	for (auto renderer : Renderer::Renderers) {
		renderer->UpdateCameraProjection();
	}
}

void Camera::UpdateCameraView() {
	cameraPos = transform->getPosition();
	
	glm::vec3 cameraFront = transform->getRotation() * glm::vec3(1, 0, 0);

	glm::vec3 cameraUp = transform->getRotation() * glm::vec3(0, 1, 0);

	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	Renderer::CurrentShaderProgram->setMat4("view", viewMatrix);
}

void Camera::RenderUIEditor() {

	if (ImGui::DragFloat((std::string("FOV##") + std::to_string(ID)).c_str(), &FOV, 0.1f)) {
		UpdateCameraProjection();
	}
}