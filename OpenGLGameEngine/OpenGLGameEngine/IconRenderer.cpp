#include "IconRenderer.h"
#include "Transform.h"

#include "Game.h"
#include "ModelLoader.h"
#include "stb_image.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

std::string IconRenderer::name = "IconRenderer";

Shader* IconRenderer::shaderProgram;

IconRenderer::IconRenderer()
{
	DisplayName = "Icon Renderer";
	iconLoaded = false;
}

IconRenderer::IconRenderer(std::string params)
{
	DisplayName = "Icon Renderer";

	iconLocation = std::string("Resources/Icons/") + params;
}

void IconRenderer::Start()
{
	Renderer::Start();

	float vertices[] = {
		// positions			// texture coords
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	if (!shaderProgram) {
		shaderProgram = new Shader("icon.vert", "icon.frag", false);
		shaderProgram->use();
	}

	shaderProgram->use();

	projectionLoc = glGetUniformLocation(CurrentShaderProgram->ID, "projection");
	viewLoc = glGetUniformLocation(CurrentShaderProgram->ID, "view");
	modelLoc = glGetUniformLocation(CurrentShaderProgram->ID, "model");

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));

	loadIcon();
}

void IconRenderer::loadIcon() {

	if (iconLoaded) {
		glDeleteTextures(0, &texture);
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char *data = stbi_load(iconLocation.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		iconLoaded = true;
	} else {
		std::cout << "Failed to load texture" << std::endl;
		iconLoaded = false;
	}
	stbi_image_free(data);
}

void IconRenderer::Render()
{
	if (!iconLoaded) 
		return;

	if (CurrentShaderProgram != shaderProgram) {
		shaderProgram->use();
		UpdateCameraProjection();

		shaderProgram->setInt("Texture", 0);

		glActiveTexture(GL_TEXTURE0);
	}

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(Camera::viewMatrix));

	//TODO Optimize this
	glBindTexture(GL_TEXTURE_2D, texture);

	glm::mat4 model = transform->GetModelMat();
	//model = glm::translate(model, transform->position);
	//
	////makes the icon face the camera along the y axis
	//glm::vec3 diff = glm::normalize(Camera::cameraPos - transform->position);
	//model = glm::rotate(model, glm::length(glm::vec3(0, atan2(diff.x, diff.z), 0)), glm::normalize(glm::vec3(0, atan2(diff.x, diff.z),0)));
	//TODO Make the icons face the camera again
	//model = glm::scale(model, transform->scale);
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void IconRenderer::UpdateCameraProjection() {
	Renderer::UpdateCameraProjection();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));
}

void IconRenderer::RenderUIEditor() {

	unsigned int flags = ImGuiInputTextFlags_EnterReturnsTrue;

	if (ImGui::InputText("Model", editorModelLocation, IM_ARRAYSIZE(editorModelLocation), flags)) {
		if (ModelLoader::CheckFileExists("Resources/Icons/" + std::string(editorModelLocation))) {
			iconLocation = "Resources/Icons/" + std::string(editorModelLocation);
			
			loadIcon();
		}
		else {
			std::cout << "Cannot Load Model" << "Resources/Icons/" + std::string(editorModelLocation) << std::endl;
		}
	}

	ImGui::Text((std::string("  loaded From:  ") + iconLocation).c_str());
}