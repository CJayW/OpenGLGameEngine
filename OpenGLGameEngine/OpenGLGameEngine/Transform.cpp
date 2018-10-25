#include "Transform.h"
#include "GameObject.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

Transform::Transform() {
	position = glm::vec3(0);
	rotation = glm::quat(glm::vec3(0, 0, 0));
	scale = glm::vec3(1);
	DisplayName = "Transform";
}

Transform::Transform(std::string message) {
	Transform();
}

Transform::~Transform() {

}
glm::mat4 Transform::GetModelMat() {
	std::vector<Transform*> parents;

	GameObject* obj = gameObject;

	parents.push_back(this);

	while (obj->parent) {
		obj = obj->parent;
		parents.push_back(obj->transform);
	}

	glm::mat4 model = glm::mat4(1);

	for (int i = parents.size() -1; i >= 0; i--) {
		std::cout << gameObject->Name << std::endl;

		model = glm::translate(model, parents[i]->position);
		model = model * glm::toMat4(parents[i]->rotation);
		model = glm::scale(model, parents[i]->scale);
	}

	return model;
}

void Transform::rotate(glm::vec3 euler) {
	glm::quat eulerQuat = glm::quat(euler / (180 / 3.1415972f));
	rotation = rotation * glm::inverse(rotation) * eulerQuat * rotation;
}

void Transform::OpenUIEditor() {
	EditorRotation = glm::eulerAngles(rotation);
	EditorRotation *= 180 / 3.14159265359;
}

void Transform::RenderUIEditor() {
	glm::vec3 lastEditorRot = EditorRotation;

	ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f);

	ImGui::DragFloat3("Rotation", glm::value_ptr(EditorRotation), 0.1f);
	ImGui::SameLine();
	if (ImGui::Button("Update")) {
		EditorRotation = glm::eulerAngles(rotation);
		EditorRotation *= 180 / 3.14159265359;
	}

	ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f);

	if (lastEditorRot != EditorRotation) {
		rotation = glm::quat(glm::vec3(0));
		rotate(EditorRotation);
	}
}