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

	void UpdateCameraProjection() override;

	void loadModel();
	//shaders
	static Shader* shaderProgram;
	unsigned int VAO, VBO, EBO, triangleCount;
	
	unsigned int viewLoc, projectionLoc, modelLoc;

	//model loading
	void RenderUIEditor() override;

	char editorModelLocation[128];

	bool loadModelFromFile;
	std::string modelLocation;

	bool modelLoaded;

};