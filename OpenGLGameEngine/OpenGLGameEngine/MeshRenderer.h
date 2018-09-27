#pragma once

#include "Renderer.h"
#include "Shader.h"

class MeshRenderer : public Renderer{
public:
	MeshRenderer();
	~MeshRenderer();
	
	float verticies[216];

	void Render() override;

	void UpdateCameraView() override;
	void UpdateCameraProjection() override;

	Shader* shaderProgram;

	unsigned int VAO, VBO;


	unsigned int viewLoc, projectionLoc, modelLoc;
};