#pragma once
#include "Renderer.h"
class IconRenderer :
	public Renderer
{
public:

	static std::string name;

	IconRenderer();
	IconRenderer(std::string params);
	~IconRenderer();

	void Start() override;
	void Render() override;

	void UpdateCameraView() override;
	void UpdateCameraProjection() override;

	unsigned int VBO, VAO, EBO;

	unsigned int viewLoc, projectionLoc, modelLoc;

	static Shader* shaderProgram;

	unsigned int texture;

	//Editor
	void RenderUIEditor() override;
};