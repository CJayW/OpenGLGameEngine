#include "TestMove.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Transform.h"

TestMove::TestMove()
{

}

TestMove::~TestMove()
{

}

void TestMove::Start() {
	//transform->position.y -= 2;
}


void TestMove::Update(double deltaTime) {
	if (Input::getKey(GLFW_KEY_I)) {
		transform->position.z -= deltaTime * 5;
	}
	if (Input::getKey(GLFW_KEY_K)) {
		transform->position.z += deltaTime * 5;
	}
	if (Input::getKey(GLFW_KEY_J)) {
		transform->position.x -= deltaTime * 5;
	}
	if (Input::getKey(GLFW_KEY_L)) {
		transform->position.x += deltaTime * 5;
	}

	/*
	float rotationSpeed = Input::getKey(GLFW_KEY_LEFT_SHIFT) ? 200 : 60;

	if (Input::getKey(GLFW_KEY_UP)) {
		transform->rotate(-glm::vec3(deltaTime * rotationSpeed,0,0));
	}
	if (Input::getKey(GLFW_KEY_DOWN)) {
		transform->rotate(glm::vec3(deltaTime * rotationSpeed,0,0));
	}
	if (Input::getKey(GLFW_KEY_LEFT)) {
		transform->rotate(glm::vec3(0,0,deltaTime * rotationSpeed));
	}
	if (Input::getKey(GLFW_KEY_RIGHT)) {
		transform->rotate(-glm::vec3(0, 0, deltaTime * rotationSpeed));
	}
	if (Input::getKey(GLFW_KEY_Q)) {
		transform->rotate(glm::vec3(0, deltaTime * rotationSpeed, 0));
	}
	if (Input::getKey(GLFW_KEY_E)) {
		transform->rotate(-glm::vec3(0, deltaTime * rotationSpeed, 0));
	}
	

	if (Input::getKey(GLFW_KEY_R)) {
		transform->rotation = glm::vec3(0, 0, 0);
	}

	if (Input::getKey(GLFW_KEY_T)) {
		std::cout << "Position: " <<glm::to_string(transform->position) << "   Rotation: " << glm::to_string(transform->rotation) << std::endl;
	}
	*/
	transform->position = glm::vec3(fmod(transform->position.x, 360), fmod(transform->position.y, 360), fmod(transform->position.z, 360));
}

