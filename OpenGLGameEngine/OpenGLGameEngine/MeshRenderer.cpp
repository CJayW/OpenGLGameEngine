#include "MeshRenderer.h"

#include <glm\gtc\type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/quaternion.hpp>

#include <glm/gtx/string_cast.hpp>

#include <vector>
#include "Transform.h"

#include "ModelLoader.h"
#include "Game.h"

std::string MeshRenderer::name = "MeshRenderer";

MeshRenderer::MeshRenderer()
{
	loadModelFromFile = false;
}

MeshRenderer::MeshRenderer(std::string params) {
	modelLocation =  "Resources/Models/" + params;
	loadModelFromFile = true;
}


MeshRenderer::~MeshRenderer() {
	loadModelFromFile = false;
}

void MeshRenderer::Start() {
	Renderer::Start();

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	if (loadModelFromFile) {
		ModelLoader::loadModel(modelLocation);
	}
	vertices = ModelLoader::Vertices;
	indices = ModelLoader::Indices;

	triangleCount = indices.size();

	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);
	if (!CurrentShaderProgram) {
		shaderProgram = new Shader("core.vert", "core.frag");
		CurrentShaderProgram = shaderProgram;
		shaderProgram->use();
	}
	else {
		shaderProgram = CurrentShaderProgram;
	}

	projectionLoc = glGetUniformLocation(CurrentShaderProgram->ID, "projection");
	viewLoc = glGetUniformLocation(CurrentShaderProgram->ID, "view");
	modelLoc = glGetUniformLocation(CurrentShaderProgram->ID, "model");

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));
}

void MeshRenderer::Render() {
//	shaderProgram->use();
	UpdateCameraView();
	UpdateCameraProjection();

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, transform->position);
	model = model * glm::toMat4(transform->rotation);
	model = glm::scale(model, transform->scale);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, triangleCount, GL_UNSIGNED_INT, 0);
}


void MeshRenderer::UpdateCameraView()
{
	Renderer::UpdateCameraView();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &cameraView[0][0]);

}

void MeshRenderer::UpdateCameraProjection()
{
	Renderer::UpdateCameraProjection();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));
}