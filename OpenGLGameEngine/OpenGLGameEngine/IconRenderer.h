#pragma once
#include "Renderer.h"
class IconRenderer :
	public Renderer
{
public:

	static std::string name;

	IconRenderer();
	IconRenderer(std::string params);

	void Start() override;
	void Render() override;
	void UpdateCameraProjection() override;

	void loadIcon();

	//Shaders
	static Shader* shaderProgram;
	unsigned int VBO, VAO, EBO;
	unsigned int viewLoc, projectionLoc, modelLoc;
	unsigned int texture;

	//loading
	std::string iconLocation;
	bool iconLoaded;

	//Editor
	void RenderUIEditor() override;
	char editorModelLocation[128];
};