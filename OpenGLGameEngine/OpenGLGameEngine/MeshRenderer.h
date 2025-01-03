#pragma once

#include "Renderer.h"
#include "Shader.h"

class MeshRenderer : public Renderer{
public:
	static std::string name;
	MeshRenderer();
	MeshRenderer(std::string modelName);
	
	std::string ToSaveString() override;

	void Start() override;
	void Render() override;

	void UpdateCameraProjection() override;

	//shaders
	static Shader* shaderProgram;
	unsigned int VAO, VBO, EBO, triangleCount;	
	unsigned int viewLoc, projectionLoc, modelLoc;

	//model loading
	void loadModel();
	
	bool loadModelFromFile;
	std::string modelLocation;
	bool modelLoaded;

	std::string loadName;

	//Editor
	void RenderUIEditor() override;
	char editorModelLocation[128];
};