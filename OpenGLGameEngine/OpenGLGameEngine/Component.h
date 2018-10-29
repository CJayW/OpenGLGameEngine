#pragma once

#include <iostream>

//for subclasses
#include "imGUI/imgui.h"
#include <glm/gtc/type_ptr.hpp>
class Transform;
class GameObject;

class Component {
public:
	Component();
	virtual ~Component();

	virtual void Start() {};
	virtual void Update(double deltaTime) {};
	virtual void Render() {};

	Transform* transform;
	GameObject* gameObject;

	virtual void RenderUIEditor() {};
	virtual void OpenUIEditor() {};

	std::string DisplayName;

	unsigned int ID;
};

