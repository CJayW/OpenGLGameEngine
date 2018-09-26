#pragma once

#include <iostream>

class Transform;
class GameObject;

class Component {
public:
	Component();
	~Component();

	virtual void Start() {};
	virtual void Update(double deltaTime) {};
	virtual void Render() {};

	Transform* transform;
	GameObject* gameObject;
};

