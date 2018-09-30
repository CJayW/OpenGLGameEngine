#pragma once
#include "Component.h"
class CameraMovement :
	public Component
{
public:
	CameraMovement();
	CameraMovement(std::string params);
	~CameraMovement();

	void Update(double deltaTime) override;

private:
	float lookSpeed;
	float moveSpeed;

};

