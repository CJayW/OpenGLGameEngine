#pragma once

#include "Component.h"
#include "Shader.h"
#include <glm/glm.hpp>

#include <vector>

class Renderer : public Component {
public:
	Renderer();
	~Renderer();

	void Start() override;

	virtual void UpdateCameraProjection();

	static Shader* CurrentShaderProgram;

	glm::mat4 cameraProjection;

	static std::vector<Renderer*> Renderers;
};