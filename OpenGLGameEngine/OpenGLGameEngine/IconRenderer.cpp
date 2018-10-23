#include "IconRenderer.h"
#include "stb_image.h"
#include "Transform.h"

#include "Game.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <glm/gtx/string_cast.hpp>


std::string IconRenderer::name = "IconRenderer";

Shader* IconRenderer::shaderProgram;

IconRenderer::IconRenderer()
{
	DisplayName = "Icon Renderer";
}

IconRenderer::IconRenderer(std::string params)
{
	DisplayName = "Icon Renderer";

	fileName = params;
}

// pointLightIcon.jpg

IconRenderer::~IconRenderer(){

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
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char *data = stbi_load((std::string("Resources/Icons/") + fileName).c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	if (!shaderProgram) {
		shaderProgram = new Shader("icon.vert", "icon.frag", false);
		shaderProgram->use();
	}

	shaderProgram->use();

	projectionLoc = glGetUniformLocation(CurrentShaderProgram->ID, "projection");
	viewLoc = glGetUniformLocation(CurrentShaderProgram->ID, "view");
	modelLoc = glGetUniformLocation(CurrentShaderProgram->ID, "model");

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));
}

void IconRenderer::Render()
{
	if (CurrentShaderProgram != shaderProgram) {
		shaderProgram->use();
		UpdateCameraView();
		UpdateCameraProjection();

		shaderProgram->setInt("Texture", 0);

		glActiveTexture(GL_TEXTURE0);
	}

	//TODO Optimize this
	glBindTexture(GL_TEXTURE_2D, texture);

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, transform->position);

	//makes the icon face the camera along the y axis
	glm::vec3 diff = glm::normalize(Camera::cameraPos - transform->position);
	model = glm::rotate(model, glm::length(glm::vec3(0, atan2(diff.x, diff.z), 0)), glm::normalize(glm::vec3(0, atan2(diff.x, diff.z),0)));

	model = glm::scale(model, transform->scale);
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void IconRenderer::UpdateCameraView() {
	Renderer::UpdateCameraView();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cameraView));

}

void IconRenderer::UpdateCameraProjection() {
	Renderer::UpdateCameraProjection();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));
}

void IconRenderer::RenderUIEditor() {

	ImGui::Text((std::string("  ") + std::string("loaded From: File")).c_str());

}
