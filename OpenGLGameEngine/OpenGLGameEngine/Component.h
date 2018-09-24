#pragma once

#include <iostream>

class Component {
public:
	Component();
	~Component();

	virtual void Start() {};
	virtual void Update(double deltaTime) {};
	virtual void Render() {};
};

