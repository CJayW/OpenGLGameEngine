#pragma once

#include "Renderer.h"
#include "Shader.h"

class MeshRenderer : public Renderer{
public:
	MeshRenderer();
	MeshRenderer(std::string params);
	~MeshRenderer();
	
	void Start() override;
	void Render() override;

	void UpdateCameraView() override;
	void UpdateCameraProjection() override;

	Shader* shaderProgram;

	unsigned int VAO, VBO, EBO;
	
	unsigned int viewLoc, projectionLoc, modelLoc;
};