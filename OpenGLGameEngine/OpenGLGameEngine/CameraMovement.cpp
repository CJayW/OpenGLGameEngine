#include "CameraMovement.h"
#include "Input.h"
#include "Transform.h"
#include "Camera.h"

#include "LevelFileManager.h"

#include "Light.h"

std::string CameraMovement::name = "CameraMovement";


CameraMovement::CameraMovement()
{
	lookSpeed = 5;
	moveSpeed = 5;
	DisplayName = name;
}

CameraMovement::CameraMovement(std::string params) {
	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');
	moveSpeed = std::stof(splitParams[0]);
	lookSpeed = std::stof(splitParams[1]);
	DisplayName = name;
}

CameraMovement::~CameraMovement()
{
}

void CameraMovement::Update(double deltaTime) {
	if (Input::mouseHidden) {
		float horizontalMoveSpeed = lookSpeed * (float)Input::getAxis(InputAxisMouseX);
		transform->rotate(glm::vec3(0, horizontalMoveSpeed, 0));

		float verticalMoveSpeed = lookSpeed * (float)Input::getAxis(InputAxisMouseY);
		transform->rotate(glm::vec3(verticalMoveSpeed, 0, verticalMoveSpeed) * (transform->rotation * glm::vec3(0, 0, 1)));
	}

	float currentMoveSpeed = Input::getKey(GLFW_KEY_LEFT_SHIFT) ? moveSpeed * 10 : moveSpeed;
	if (Input::getKey(GLFW_KEY_W)) {
		transform->position += (transform->rotation * glm::vec3(1, 0, 0)) * glm::vec3(deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_S)) {
		transform->position -= (transform->rotation * glm::vec3(1, 0, 0)) * glm::vec3(deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_A)) {
		transform->position -= (transform->rotation * glm::vec3(0, 0, 1)) * glm::vec3(deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_D)) {
		transform->position += (transform->rotation * glm::vec3(0, 0, 1)) * glm::vec3(deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_E)) {
		transform->position += (transform->rotation * glm::vec3(0, 1, 0)) * glm::vec3(deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_Q)) {
		transform->position -= (transform->rotation * glm::vec3(0, 1, 0)) * glm::vec3(deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed, deltaTime * currentMoveSpeed);
	}
}

void CameraMovement::RenderUIEditor() {
	ImGui::DragFloat("moveSpeed", &moveSpeed);
	ImGui::DragFloat("lookSpeed", &lookSpeed);
}