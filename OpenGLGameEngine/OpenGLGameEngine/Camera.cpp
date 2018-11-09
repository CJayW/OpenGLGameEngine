#include "Camera.h"
#include "Game.h"

#include <glm\gtc\type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Transform.h"

#include "Renderer.h"
#include "IconRenderer.h"

#include "LevelFileManager.h"

glm::mat4 Camera::projection;
glm::mat4 Camera::viewMatrix;
glm::vec3 Camera::cameraPos;

float Camera::FOV = 60;
float Camera::NearClippingPlane = 0.1;
float Camera::FarClippingPlane = 100;

std::string Camera::name = "Camera";

Camera::Camera()
{
	DisplayName = name;
}

Camera::Camera(std::string params) {
	std::vector<std::string> sParams = LevelFileManager::splitBy(params, ',');

	FOV = std::stof(sParams[0]);
	DisplayName = name;

	if (sParams.size() > 1) {
		NearClippingPlane = std::stof(sParams[1]);
		FarClippingPlane = std::stof(sParams[2]);
	}

}

Camera::~Camera()
{	
	Game::camera = NULL;
}

std::string Camera::ToSaveString() {
	std::string str = "";
	
	str += name;
	str += '(';
	str += std::to_string(FOV);
	str += ",";
	str += std::to_string(NearClippingPlane);
	str += ",";
	str += std::to_string(FarClippingPlane);
	

	return str;
}

void Camera::Start() {
	UpdateCameraView();
	UpdateCameraProjection();
	IconRenderer* icon =     gameObject->addComponent<IconRenderer>("CameraIcon.jpg");
}

void Camera::Update(double deltaTime) {
}

void Camera::UpdateCameraProjection() {

	EditorDebug::Log("Update proj");

	float ratio = ((float)Game::width / (float)Game::height);
	projection = glm::perspective(glm::radians(FOV), ratio, 0.1f, 100.0f);
	
	for (auto renderer : Renderer::Renderers) {
		renderer->UpdateCameraProjection();
	}
}

void Camera::UpdateCameraView() {
	cameraPos = transform->getPosition();
	
	glm::vec3 cameraFront = transform->getRotation() * glm::vec3(1, 0, 0);

	glm::vec3 cameraUp = transform->getRotation() * glm::vec3(0, 1, 0);

	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	if (Renderer::CurrentShaderProgram) {
		Renderer::CurrentShaderProgram->setMat4("view", viewMatrix);
	}
}

void Camera::RenderUIEditor() {

	if (ImGui::DragFloat((std::string("FOV##") + std::to_string(ID)).c_str(), &FOV, 0.1f)) {
		UpdateCameraProjection();
	}
	if (ImGui::DragFloat(("Near Clipping Plane##" + std::to_string(ID)).c_str(), &NearClippingPlane)) {
		UpdateCameraProjection();
	}
	if (ImGui::DragFloat(("Far Clipping Plane##" + std::to_string(ID)).c_str(), &FarClippingPlane)) {
		UpdateCameraProjection();
	}
}