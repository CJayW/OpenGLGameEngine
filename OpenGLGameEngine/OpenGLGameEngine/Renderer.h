#pragma once

#include "Component.h"
#include "Shader.h"
#include <glm/glm.hpp>

class Renderer : public Component {
public:
	Renderer();
	~Renderer();

	void Start() override;

	virtual void UpdateCameraView();
	virtual void UpdateCameraProjection();

	static Shader* CurrentShaderProgram;

	glm::mat4 cameraProjection;
	glm::mat4 cameraView;
};