#pragma once
#include "Include.h"

class move : public Component {
public:

	static std::string name;

	move();
	move(std::string params);
	~move();

	std::string ToSaveString() override;

	void Start() override;
	void Render() override;
	void Update(double deltaTime) override;
	

	//Editor
	void RenderUIEditor() override;
};