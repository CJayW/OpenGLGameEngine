#pragma once

#include "Component.h"

class MeshRenderer : public Component{
public:
	MeshRenderer();
	~MeshRenderer();
	
	void Start() override;
	
};

