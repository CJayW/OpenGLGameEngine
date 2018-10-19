#include "Rigidbody.h"
#include "Transform.h"

#include "Input.h"
#include "LevelFileManager.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


std::string Rigidbody::name = "Rigidbody";

Rigidbody::Rigidbody()
{
	velocity = glm::vec3(0);
	mass = 1.0f;
	drag = 0.5f;

	gravity = glm::vec3(0, -15.0f, 0);

}

Rigidbody::Rigidbody(std::string params)
{
	std::vector<std::string> sParams = LevelFileManager::splitBy(params, ',');

	velocity = LevelFileManager::stringToVec3(sParams[0]);
	mass = std::stof(sParams[1]);
	drag = std::stof(sParams[2]);

	gravity = glm::vec3(0, -15.0f, 0);
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Start()
{
	DisplayName = name;
}

void Rigidbody::Update(double deltaTime)
{
	if (Input::getKey(GLFW_KEY_B)) {
		addForce(0, 0.008 , 0);
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

void Rigidbody::RenderUIEditor() {

	ImGui::DragFloat("Mass", &mass, 0.1f);
	ImGui::DragFloat("Drag", &drag, 0.1f);
	ImGui::DragFloat3("Gravity", glm::value_ptr(gravity), 0.1f);
	ImGui::DragFloat3("Velocity", glm::value_ptr(velocity), 0.1f);
}