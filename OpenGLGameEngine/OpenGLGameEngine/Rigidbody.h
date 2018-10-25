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

	//Helper Functions
	void addForce(glm::vec3 force);
	void addForce(float x, float y, float z);

private:
	//Physics
	float mass;
	float drag;
	glm::vec3 gravity;
	glm::vec3 velocity;

	//Editor
	void RenderUIEditor() override;
};