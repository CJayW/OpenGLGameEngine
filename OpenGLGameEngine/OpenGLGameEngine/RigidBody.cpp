#include "Rigidbody.h"
#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "Input.h"

std::string Rigidbody::name = "Rigidbody";

Rigidbody::Rigidbody()
{
}

Rigidbody::Rigidbody(std::string params)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Start()
{
	velocity = glm::vec3(0);
	gravity = glm::vec3(0, -9.8f, 0);
	drag = 0.5f;
	mass = 1.0f;

	playing = false;
}

void Rigidbody::Update(double deltaTime)
{
	if (!playing) {

		if (Input::getKeyDown(GLFW_KEY_O)) {
			playing = true;
		}
		else {
			return;
		}
	}
	
	glm::vec3 temp = velocity;
	temp *= drag;
	temp *= drag;
	temp *= deltaTime;

	velocity -= temp;

	temp = velocity;
	
	temp *= deltaTime;

	transform->position += temp;
	
	temp = gravity;
	temp *= deltaTime;

	addForce(temp);

	if (transform->position.y <= 0) {
		velocity *= 0;
	}
}

void Rigidbody::addForce(glm::vec3 force)
{
	velocity += force / mass;
}

void Rigidbody::addForce(float x, float y, float z)
{
	addForce(glm::vec3(x, y, z));
}