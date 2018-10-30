#pragma once
#include "Component.h"
class CameraMovement :
	public Component
{
public:
	static std::string name;

	CameraMovement();
	CameraMovement(std::string params);
	~CameraMovement();

	std::string ToSaveString() override;

	void Update(double deltaTime) override;

private:
	float lookSpeed;
	float moveSpeed;

	//Editor
	void RenderUIEditor() override;
};

