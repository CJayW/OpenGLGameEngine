#include "Renderer.h"

#include "Camera.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	//TODO Add an ID to the components to improve this code

	for (int i = 0; i < Renderers.size(); i++) {
		if (Renderers[i]->gameObject == gameObject) {
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