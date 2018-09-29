#pragma once
#include "Component.h"
class CameraMovement :
	public Component
{
public:
	CameraMovement();
	~CameraMovement();

	void Update(double deltaTime) override;
};

