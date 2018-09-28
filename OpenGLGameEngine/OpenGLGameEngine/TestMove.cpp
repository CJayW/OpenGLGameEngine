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
	transform->position.y -= 2;
}


void TestMove::Update(double deltaTime) {

	//transform->position.z -= Input::getAxis(InputAxisMouseY) * deltaTime;
	//transform->position.x -= Input::getAxis(InputAxisMouseX) * deltaTime;

	if (Input::getKey(GLFW_KEY_W)) {
		transform->position.z -= deltaTime * 5;
	}
	if (Input::getKey(GLFW_KEY_S)) {
		transform->position.z += deltaTime * 5;
	}
	if (Input::getKey(GLFW_KEY_A)) {
		transform->position.x -= deltaTime * 5;
	}
	if (Input::getKey(GLFW_KEY_D)) {
		transform->position.x += deltaTime * 5;
	}

	float rotationSpeed = Input::getKey(GLFW_KEY_LEFT_SHIFT) ? 200 : 60;

	if (Input::getKey(GLFW_KEY_UP)) {
		//transform->rotation.x -= deltaTime * rotationSpeed;
		//transform->rotation.x += transform->rotation.x < 0 ? 360 : 0;
		transform->rotate(-glm::vec3(deltaTime * rotationSpeed,0,0));
	}
	if (Input::getKey(GLFW_KEY_DOWN)) {
		//transform->rotation.x += deltaTime * rotationSpeed;
		//transform->rotation.x = transform->rotation.x > 360 ? 360 - transform->rotation.x : transform->rotation.x;
		transform->rotate(glm::vec3(deltaTime * rotationSpeed,0,0));
	}
	if (Input::getKey(GLFW_KEY_LEFT)) {
		//transform->rotation.z += deltaTime * rotationSpeed;
		//transform->rotation.z = transform->rotation.z > 360 ? 360 - transform->rotation.z : transform->rotation.z;
		transform->rotate(glm::vec3(0,0,deltaTime * rotationSpeed));
	}
	if (Input::getKey(GLFW_KEY_RIGHT)) {
		//transform->rotation.z -= deltaTime * rotationSpeed;
		//transform->rotation.z += transform->rotation.z < 0 ? 360 : 0;
		transform->rotate(-glm::vec3(0, 0, deltaTime * rotationSpeed));
	}
	if (Input::getKey(GLFW_KEY_Q)) {
		//transform->rotation.y += deltaTime * rotationSpeed;
		//transform->rotation.y = transform->rotation.y > 360 ? 360 - transform->rotation.y : transform->rotation.y;
		transform->rotate(glm::vec3(0, deltaTime * rotationSpeed, 0));
	}
	if (Input::getKey(GLFW_KEY_E)) {
		//transform->rotation.y -= deltaTime * rotationSpeed;
		//transform->rotation.y += transform->rotation.y < 0 ? 360 : 0;	
		transform->rotate(-glm::vec3(0, deltaTime * rotationSpeed, 0));
	}

	std::cout << glm::to_string(glm::eulerAngles(transform->rotation)  * (180 / 3.1415972f)) << " Euler Angles Values" << std::endl;

	if (Input::getKey(GLFW_KEY_R)) {
		transform->rotation = glm::vec3(0, 0, 0);
	}

	if (Input::getKey(GLFW_KEY_T)) {
		std::cout << "Position: " <<glm::to_string(transform->position) << "   Rotation: " << glm::to_string(transform->rotation) << std::endl;
	}

	transform->position = glm::vec3(fmod(transform->position.x, 360), fmod(transform->position.y, 360), fmod(transform->position.z, 360));

}

