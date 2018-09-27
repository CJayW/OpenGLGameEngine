#include "MeshRenderer.h"

#include <glm\gtc\type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/quaternion.hpp>

#include <glm/gtx/string_cast.hpp>


#include "Transform.h"

MeshRenderer::MeshRenderer() {
	std::cout << "base Construct" << std::endl;
	float vertices[] = {
		//Pos						//UV coordinates
		-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f
	};

	unsigned int VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	shaderProgram = new Shader("core.vert", "core.frag");
	shaderProgram->use();

	projectionLoc = glGetUniformLocation(shaderProgram->ID, "projection");
	viewLoc = glGetUniformLocation(shaderProgram->ID, "view");
	modelLoc = glGetUniformLocation(shaderProgram->ID, "model");

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));
}


MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Render() {

	glm::mat4 model = glm::mat4(1);

	model = glm::translate(model, transform->position);

	glm::vec3 rotationDir = transform->rotation == glm::vec3(0,0,0) ? glm::vec3(1,1,1) : glm::normalize(transform->rotation);

	float mag = glm::length(transform->rotation);

	glm::quat myQuat;
	myQuat = glm::quat(glm::vec3(transform->rotation) / (180 / 3.1415972f));
	// glm::quatToMat(myQuat);

	model = model * glm::toMat4(myQuat);// *model;
		
		
	//glm::rotate(model, glm::radians(mag), rotationDir);
	
	/*
	model = glm::rotate(model, glm::radians(transform->rotation.x), glm::vec3(1,0,0));
	model = glm::rotate(model, glm::radians(transform->rotation.y), glm::vec3(0,1,0));
	model = glm::rotate(model, glm::radians(transform->rotation.z), glm::vec3(0,0,1));
	*/

	std::cout << glm::to_string(transform->rotation) << std::endl;
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, 36);
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
