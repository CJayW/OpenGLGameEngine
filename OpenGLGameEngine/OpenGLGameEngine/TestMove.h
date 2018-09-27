#pragma once
#include "Component.h"
class TestMove : public Component
{
public:
	TestMove();
	~TestMove();

	void Start() override;

	void Update(double deltaTime) override;

};

