#include "MeshRenderer.h"

#include <glm\gtc\type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/quaternion.hpp>

#include <glm/gtx/string_cast.hpp>


#include "Transform.h"

MeshRenderer::MeshRenderer() {

}

MeshRenderer::MeshRenderer(std::string params) {

}


MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Start() {
	Renderer::Start();
	float vertices[] = {
		-1.000000f,  -1.000000f,   0.734375f,       1.0f, 1.0f,  0.5f,
		-1.024932f,   0.874428f,  -0.890114f,       1.0f, 1.0f,  0.5f,
		-1.000000f,  -1.000000f,  -1.064992f,       1.0f, 1.0f,  0.5f,
		-1.000000f,   1.000000f,   1.000000f,       1.0f, 1.0f,  0.5f,
		 0.905796f,   0.904748f,  -1.000000f,       1.0f, 1.0f,  0.5f,
		-1.024932f,   0.874428f,  -0.890114f,       1.0f, 1.0f,  0.5f,

		 1.000000f,   1.000000f,   1.000000f,       1.0f, 0.5f,  0.0f,
		 1.000000f,  -0.848065f,  -1.000000f,       1.0f, 0.5f,  0.0f,
		 0.905796f,   0.904748f,  -1.000000f,       1.0f, 0.5f,  0.0f,
		 1.000000f,  -0.848065f,  -1.000000f,       1.0f, 0.5f,  0.0f,
		-1.000000f,  -1.000000f,   0.734375f,       1.0f, 0.5f,  0.0f,
		-1.000000f,  -1.000000f,  -1.064992f,       1.0f, 0.5f,  0.0f,

		-1.024932f,   0.874428f,  -0.890114f,       0.5f, 0.0f,  0.5f,
		 1.000000f,  -0.848065f,  -1.000000f,       0.5f, 0.0f,  0.5f,
		-1.000000f,  -1.000000f,  -1.064992f,       0.5f, 0.0f,  0.5f,
		-1.000000f,   1.000000f,   1.000000f,       0.5f, 0.0f,  0.5f,
		 1.000000f,  -1.000000f,   1.000000f,       0.5f, 0.0f,  0.5f,
		 1.000000f,   1.000000f,   1.000000f,       0.5f, 0.0f,  0.5f,

		-1.000000f,  -1.000000f,   0.734375f,       0.0f, 0.5f,  1.0f,
		-1.000000f,   1.000000f,   1.000000f,       0.0f, 0.5f,  1.0f,
		-1.024932f,   0.874428f,  -0.890114f,       0.0f, 0.5f,  1.0f,
		-1.000000f,   1.000000f,   1.000000f,       0.0f, 0.5f,  1.0f,
		 1.000000f,   1.000000f,   1.000000f,       0.0f, 0.5f,  1.0f,
		 0.905796f,   0.904748f,  -1.000000f,       0.0f, 0.5f,  1.0f,

		 1.000000f,   1.000000f,   1.000000f,       0.5f, 1.0f,  0.5f,
		 1.000000f,  -1.000000f,   1.000000f,       0.5f, 1.0f,  0.5f,
		 1.000000f,  -0.848065f,  -1.000000f,       0.5f, 1.0f,  0.5f,
		 1.000000f,  -0.848065f,  -1.000000f,       0.5f, 1.0f,  0.5f,
		 1.000000f,  -1.000000f,   1.000000f,       0.5f, 1.0f,  0.5f,
		-1.000000f,  -1.000000f,   0.734375f,       0.5f, 1.0f,  0.5f,

		-1.024932f,   0.874428f,  -0.890114f,       1.0f, 0.5f,  0.0f,
		 0.905796f,   0.904748f,  -1.000000f,       1.0f, 0.5f,  0.0f,
		 1.000000f,  -0.848065f,  -1.000000f,       1.0f, 0.5f,  0.0f,
		-1.000000f,   1.000000f,   1.000000f,       1.0f, 0.5f,  0.0f,
		-1.000000f,  -1.000000f,   0.734375f,       1.0f, 0.5f,  0.0f,
		 1.000000f,  -1.000000f,   1.000000f,       1.0f, 0.5f,  0.0f
	};

	unsigned int indices[] = {
		0 ,  1 ,  2,
		3 ,  4 ,  5,
		6 ,  7 ,  8,
		9 ,  10,  11,
		12,  13,  14,
		15,  16,  17,
		18,  19,  20,
		21,  22,  23,
		24,  25,  26,
		27,  28,  29,
		30,  31,  32,
		33,  34,  35
	};
	

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

void MeshRenderer::Render() {
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, transform->position);
	model = model * glm::toMat4(transform->rotation);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//glDrawArrays(GL_TRIANGLES, 0, 36);
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