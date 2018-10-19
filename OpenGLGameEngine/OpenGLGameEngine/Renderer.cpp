#include "Renderer.h"

#include "Camera.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

std::vector<Renderer*> Renderer::Renderers;

Shader* Renderer::CurrentShaderProgram;

void Renderer::Start() {
	Renderers.push_back(this);
}

void Renderer::UpdateCameraView() {
	cameraView = Camera::viewMatrix;
}

void Renderer::UpdateCameraProjection() {
	cameraProjection = Camera::projection;
}