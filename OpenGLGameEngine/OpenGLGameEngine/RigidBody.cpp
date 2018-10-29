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

	DisplayName = name;
}

Rigidbody::Rigidbody(std::string params)
{
	std::vector<std::string> sParams = LevelFileManager::splitBy(params, ',');

	velocity = LevelFileManager::stringToVec3(sParams[0]);
	mass = std::stof(sParams[1]);
	drag = std::stof(sParams[2]);

	gravity = glm::vec3(0, -15.0f, 0);

	DisplayName = name;
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Start()
{
}

void Rigidbody::Update(double deltaTime)
{

	//Drag
	glm::vec3 temp = velocity;
	//TODO velocity^2 ??
	temp *= drag;
	temp *= deltaTime;
	velocity -= temp;

	//Movement
	temp = velocity;
	temp *= deltaTime;
	transform->localPos += temp;
	
	//Gravity
	temp = gravity;
	temp *= deltaTime;
	addForce(temp);

	//Super Complex Collision Check
	if (transform->localPos.y <= 0) {
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
	std::string idTag = "##" + std::to_string(ID);
	ImGui::DragFloat ((std::string("Mass"    ) + idTag).c_str(), &mass, 0.1f);
	ImGui::DragFloat ((std::string("Drag"    ) + idTag).c_str(), &drag, 0.1f);
	ImGui::DragFloat3((std::string("Gravity" ) + idTag).c_str(), glm::value_ptr(gravity), 0.1f);
	ImGui::DragFloat3((std::string("Velocity") + idTag).c_str(), glm::value_ptr(velocity), 0.1f);
}