#include "CameraMovement.h"
#include "Input.h"
#include "Transform.h"
#include "Camera.h"

CameraMovement::CameraMovement()
{
}


CameraMovement::~CameraMovement()
{
}

void CameraMovement::Update(double deltaTime) {

	float mouseMoveSpeed = 5.0f;
	float horizontalMoveSpeed = deltaTime * mouseMoveSpeed * Input::getAxis(InputAxisMouseX);
	transform->rotate(glm::vec3(0, horizontalMoveSpeed, 0));

	float verticalMoveSpeed = deltaTime * mouseMoveSpeed * Input::getAxis(InputAxisMouseY);
	transform->rotate(glm::vec3(verticalMoveSpeed, 0, verticalMoveSpeed) * (transform->rotation * glm::vec3(0, 0, 1)));


	if (Input::getKey(GLFW_KEY_W)) {
		transform->position += (transform->rotation * glm::vec3(1, 0, 0)) * glm::vec3(deltaTime * 5, deltaTime * 5, deltaTime * 5);
	}
	if (Input::getKey(GLFW_KEY_S)) {
		transform->position -= (transform->rotation * glm::vec3(1, 0, 0)) * glm::vec3(deltaTime * 5, deltaTime * 5, deltaTime * 5);
	}
	if (Input::getKey(GLFW_KEY_A)) {
		transform->position -= (transform->rotation * glm::vec3(0, 0, 1)) * glm::vec3(deltaTime * 5, deltaTime * 5, deltaTime * 5);
	}
	if (Input::getKey(GLFW_KEY_D)) {
		transform->position += (transform->rotation * glm::vec3(0, 0, 1)) * glm::vec3(deltaTime * 5, deltaTime * 5, deltaTime * 5);
	}
	if (Input::getKey(GLFW_KEY_E)) {
		transform->position += (transform->rotation * glm::vec3(0, 1, 0)) * glm::vec3(deltaTime * 5, deltaTime * 5, deltaTime * 5);
	}
	if (Input::getKey(GLFW_KEY_Q)) {
		transform->position -= (transform->rotation * glm::vec3(0, 1, 0)) * glm::vec3(deltaTime * 5, deltaTime * 5, deltaTime * 5);
	}


	if (Input::getKey(GLFW_KEY_R)) {
		transform->rotation = glm::vec3(0, 0, 0);
	}

	if (Input::getKey(GLFW_KEY_T)) {
		std::cout << "Position: " << glm::to_string(transform->position) << "   Rotation: " << glm::to_string(transform->rotation) << std::endl;
	}

	transform->position = glm::vec3(fmod(transform->position.x, 360), fmod(transform->position.y, 360), fmod(transform->position.z, 360));


}
