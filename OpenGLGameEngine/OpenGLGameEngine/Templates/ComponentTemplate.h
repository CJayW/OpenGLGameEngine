#pragma once
#include "Component.h"
class ComponentTemplate :
	public Component
{
public:

	static std::string name;

	ComponentTemplate();
	ComponentTemplate(std::string params);
	~ComponentTemplate();

	void Start() override;
	void Update(double deltaTime) override;
	void Render() override;
};