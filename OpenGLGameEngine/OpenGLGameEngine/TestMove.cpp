#include "TestMove.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Transform.h"
#include "LevelFileManager.h"
std::string TestMove::name = "TestMove";

TestMove::TestMove()
{
	moveSpeed = 5;
	rotationSpeed = 60;
	rotationSpeedMultiplier = 3.333;
}

TestMove::TestMove(std::string params) {
	std::vector<std::string> splitParams = LevelFileManager::splitBy(params, ',');
	moveSpeed = std::stof(splitParams[0]);
	rotationSpeed = std::stof(splitParams[1]);
	rotationSpeedMultiplier = std::stof(splitParams[2]);
}

TestMove::~TestMove()
{

}

void TestMove::Start() {
	//transform->position.y -= 2;
}


void TestMove::Update(double deltaTime) {
	if (Input::getKey(GLFW_KEY_I)) {
		transform->position.z -= deltaTime * moveSpeed;
	}
	if (Input::getKey(GLFW_KEY_K)) {
		transform->position.z += deltaTime * moveSpeed;
	}
	if (Input::getKey(GLFW_KEY_J)) {
		transform->position.x -= deltaTime * moveSpeed;
	}
	if (Input::getKey(GLFW_KEY_L)) {
		transform->position.x += deltaTime * moveSpeed;
	}

	
	float RotationSpeed = Input::getKey(GLFW_KEY_LEFT_SHIFT) ? rotationSpeed * rotationSpeedMultiplier : rotationSpeed;

	if (Input::getKey(GLFW_KEY_UP)) {
		transform->rotate(-glm::vec3(deltaTime * RotationSpeed,0,0));
	}
	if (Input::getKey(GLFW_KEY_DOWN)) {
		transform->rotate(glm::vec3(deltaTime * RotationSpeed,0,0));
	}
	if (Input::getKey(GLFW_KEY_LEFT)) {
		transform->rotate(glm::vec3(0,0,deltaTime * RotationSpeed));
	}
	if (Input::getKey(GLFW_KEY_RIGHT)) {
		transform->rotate(-glm::vec3(0, 0, deltaTime * RotationSpeed));
	}
	if (Input::getKey(GLFW_KEY_DELETE)) {
		transform->rotate(glm::vec3(0, deltaTime * RotationSpeed, 0));
	}
	if (Input::getKey(GLFW_KEY_PAGE_DOWN)) {
		transform->rotate(-glm::vec3(0, deltaTime * RotationSpeed, 0));
	}
	
	transform->position = glm::vec3(fmod(transform->position.x, 360), fmod(transform->position.y, 360), fmod(transform->position.z, 360));
}

