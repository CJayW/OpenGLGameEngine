#pragma once

#include "Renderer.h"
#include "Shader.h"

class MeshRenderer : public Renderer{
public:

	static std::string name;

	MeshRenderer();
	MeshRenderer(std::string modelName);

	~MeshRenderer();
	
	void Start() override;
	void Render() override;

	void UpdateCameraView() override;
	void UpdateCameraProjection() override;

	//shaders
	static Shader* shaderProgram;
	unsigned int VAO, VBO, EBO, triangleCount;
	
	unsigned int viewLoc, projectionLoc, modelLoc;

	//model loading
	void RenderUIEditor() override;

	bool loadModelFromFile;
	std::string modelLocation;

};