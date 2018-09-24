#pragma once
#include "Component.h"
#include <string>
class Transform : public Component{
public:
	Transform();
	Transform(std::string message);

	~Transform();

};

