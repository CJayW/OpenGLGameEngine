#include "Transform.h"
#include "GameObject.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

Transform::Transform() {
	localPos = glm::vec3(0);
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
		model = glm::translate(model, parents[i]->localPos);
		model = model * glm::toMat4(parents[i]->rotation);
		model = glm::scale(model, parents[i]->scale);
	}

	return model;
}

glm::vec3 Transform::getPosition() {
	//optimized to use this instead of glm::decompose
	//#include <glm/gtx/matrix_decompose.hpp>

	glm::mat4 model = GetModelMat();

	glm::vec3 temp = glm::vec3(model[3]);
	temp /= model[3][3];

	return temp;
}
#include <glm/gtx/matrix_decompose.hpp>

glm::quat Transform::getRotation() {
	//TODO Optimize this
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 skew;
	glm::quat rot;
	glm::vec4 perspectivce;
	glm::decompose(GetModelMat(), scale, rot, pos, skew, perspectivce);

	return rot;
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

	ImGui::DragFloat3("Position", glm::value_ptr(localPos), 0.1f);

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