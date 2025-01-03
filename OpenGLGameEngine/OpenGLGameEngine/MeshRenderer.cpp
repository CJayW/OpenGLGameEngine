#include "MeshRenderer.h"
#include "Transform.h"
#include "ModelLoader.h"
#include "Game.h"

#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "EditorDebug.h"

std::string MeshRenderer::name = "MeshRenderer";

Shader* MeshRenderer::shaderProgram;

MeshRenderer::MeshRenderer()
{
	loadModelFromFile = false;
	DisplayName = name;
	modelLoaded = false;
}

MeshRenderer::MeshRenderer(std::string params) {
	modelLocation = Game::ProjectLocation + "/Resources/Models/" + params;
	loadModelFromFile = true;

	loadName = params;

	DisplayName = name;
}


std::string MeshRenderer::ToSaveString() {
	std::string str;
	str += name;
	str += "(";
	str += loadName;

	return str;
}

void MeshRenderer::Start() {
	Renderer::Start();

	if (!shaderProgram) {
		shaderProgram = new Shader("core.vert", "core.frag");
	}
	if (CurrentShaderProgram != shaderProgram) {
		shaderProgram->use();
		if (Game::camera != nullptr) {
			shaderProgram->setMat4("view", Camera::viewMatrix);
		}
		UpdateCameraProjection();
	}

	projectionLoc = glGetUniformLocation(CurrentShaderProgram->ID, "projection");
	viewLoc = glGetUniformLocation(CurrentShaderProgram->ID, "view");
	modelLoc = glGetUniformLocation(CurrentShaderProgram->ID, "model");

	UpdateCameraProjection();


	if (!loadModelFromFile) {
		modelLoaded = false;
	}
	else {
		loadModel();
	}
}

void MeshRenderer::loadModel() {
	if (modelLoaded) {
		glDeleteBuffers(0, &EBO);
		glDeleteBuffers(0, &VAO);
		glDeleteBuffers(0, &VBO);
	}

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	ModelLoader::loadModel(modelLocation);

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

	modelLoaded = true;
}

void MeshRenderer::Render() {
	if (!modelLoaded)
		return;

	if (CurrentShaderProgram != shaderProgram) {
		shaderProgram->use();
		if (Game::camera != nullptr) {
			shaderProgram->setMat4("view", Camera::viewMatrix);
			UpdateCameraProjection();
		}
	}

	shaderProgram->setMat4("view", Camera::viewMatrix);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform->GetModelMat()));

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, triangleCount, GL_UNSIGNED_INT, 0);
}

void MeshRenderer::UpdateCameraProjection()
{
	Renderer::UpdateCameraProjection();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));

}

void MeshRenderer::RenderUIEditor() {

	unsigned int flags = ImGuiInputTextFlags_EnterReturnsTrue;
	
	if (ImGui::InputText((std::string("Model##") + std::to_string(ID)).c_str(), editorModelLocation, IM_ARRAYSIZE(editorModelLocation), flags)) {
		if (ModelLoader::CheckFileExists(Game::ProjectLocation + "/Resources/Models/" + std::string(editorModelLocation))) {
			modelLocation = Game::ProjectLocation + "/Resources/Models/" + std::string(editorModelLocation);
			loadModel();
			loadName = std::string(editorModelLocation);
		} else {
			EditorDebug::ErrorLog("Cannot Load Model");
		}
	}

	ImGui::Text((std::string("Loaded From: ") + loadName).c_str());
}