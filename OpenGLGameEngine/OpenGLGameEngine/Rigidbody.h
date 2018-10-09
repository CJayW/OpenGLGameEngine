#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class Rigidbody :
	public Component
{
public:
	static std::string name;

	Rigidbody();
	Rigidbody(std::string params);
	~Rigidbody();

	void Start() override;
	void Update(double deltaTime) override;

	float mass;
	glm::vec3 velocity;
	
	float drag;

	glm::vec3 gravity;

	void addForce(glm::vec3 force);
	void addForce(float x, float y, float z);
	
	bool playing;
};