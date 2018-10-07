#include "Renderer.h"

#include "Camera.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

Shader* Renderer::CurrentShaderProgram;

void Renderer::Start() {
	Camera::AddRenderer(this);
}

void Renderer::UpdateCameraView() {
	cameraView = Camera::viewMatrix;
}

void Renderer::UpdateCameraProjection() {
	cameraProjection = Camera::projection;
}