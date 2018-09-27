#pragma once

#include "Component.h"

#include <glm/glm.hpp>

class Renderer : public Component {
public:
	Renderer();
	~Renderer();

	void Start() override;

	virtual void UpdateCameraView();
	virtual void UpdateCameraProjection();



	glm::mat4 cameraProjection;
	glm::mat4 cameraView;
};