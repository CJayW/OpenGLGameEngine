#pragma once
#include "Component.h"
class TestMove : public Component
{
public:
	static std::string name;

	TestMove();
	TestMove(std::string params);
	~TestMove();

	void Start() override;

	void Update(double deltaTime) override;

private:
	float moveSpeed;
	float rotationSpeed;
	float rotationSpeedMultiplier;

};