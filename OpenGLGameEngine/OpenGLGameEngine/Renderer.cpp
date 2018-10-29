#include "Renderer.h"

#include "Camera.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	for (int i = 0; (size_t)i < Renderers.size(); i++) {
		if (Renderers[i]->ID == ID) {
			Renderers.erase(Renderers.begin() + i);
			return;
		}
	}
}

std::vector<Renderer*> Renderer::Renderers;

Shader* Renderer::CurrentShaderProgram;

void Renderer::Start() {
	Renderers.push_back(this);
}



void Renderer::UpdateCameraProjection() {
	cameraProjection = Camera::projection;
}