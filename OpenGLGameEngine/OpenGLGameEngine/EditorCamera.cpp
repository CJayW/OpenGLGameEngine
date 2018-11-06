#include "EditorCamera.h"

#include <iostream>
#include "Renderer.h"
#include "Camera.h"

#include "Input.h"
#include "Time.h"
EditorCamera::EditorCamera() {
	Rot = glm::quat(glm::vec3(0));
	Pos = glm::vec3(0);
}


EditorCamera::~EditorCamera() {
}

void EditorCamera::UpdateCameraView() {
	glm::vec3 cameraFront = Rot * glm::vec3(1, 0, 0);

	glm::vec3 cameraUp = Rot * glm::vec3(0, 1, 0);
	float ratio = ((float)Game::width / (float)Game::height);

	Camera::projection = glm::perspective(glm::radians(60.0f), ratio, 0.1f, 100.0f);

	Camera::viewMatrix = glm::lookAt(Pos, Pos + cameraFront, cameraUp);

	if(Renderer::CurrentShaderProgram != nullptr)
		Renderer::CurrentShaderProgram->setMat4("view", Camera::viewMatrix);
}

void EditorCamera::Update() {
	float lookSpeed = 0.1f;
	if (Input::cursorHidden){
		float horizontalMoveSpeed = lookSpeed * (float)Input::getAxis(InputAxisMouseX);
		rotate(glm::vec3(0, horizontalMoveSpeed, 0));

		float verticalMoveSpeed = lookSpeed * (float)Input::getAxis(InputAxisMouseY);
		rotate(glm::vec3(verticalMoveSpeed, 0, verticalMoveSpeed) * (Rot * glm::vec3(0, 0, 1)));
	}

	float currentMoveSpeed = Input::getKey(GLFW_KEY_LEFT_SHIFT) ? 50.0f : 5.0f;
	if (Input::getKey(GLFW_KEY_W)) {
		Pos += (Rot * glm::vec3(1, 0, 0)) * glm::vec3(Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_S)) {
		Pos -= (Rot * glm::vec3(1, 0, 0)) * glm::vec3(Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_A)) {
		Pos -= (Rot * glm::vec3(0, 0, 1)) * glm::vec3(Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_D)) {
		Pos += (Rot * glm::vec3(0, 0, 1)) * glm::vec3(Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_E)) {
		Pos += (Rot * glm::vec3(0, 1, 0)) * glm::vec3(Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed);
	}
	if (Input::getKey(GLFW_KEY_Q)) {
		Pos -= (Rot * glm::vec3(0, 1, 0)) * glm::vec3(Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed, Time::deltaTime * currentMoveSpeed);
	}

	if (Input::getKeyDown(GLFW_KEY_ESCAPE)) {
		Input::SetCursorState(Input::cursorHidden);
	}
	Camera::cameraPos = Pos;
}

void EditorCamera::rotate(glm::vec3 euler) {
	glm::quat eulerQuat = glm::quat(euler / (180 / 3.1415972f));
	Rot = Rot * glm::inverse(Rot) * eulerQuat * Rot;
}