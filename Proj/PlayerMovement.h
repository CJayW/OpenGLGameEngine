#pragma once
#include "Include.h"

class PlayerMovement : public Component {
public:

	static std::string name;

	PlayerMovement();
	PlayerMovement(std::string params);
	~PlayerMovement();

	std::string ToSaveString() override;

	void Start() override;
	void Render() override;
	void Update(double deltaTime) override;
	

	//Editor
	void RenderUIEditor() override;
};