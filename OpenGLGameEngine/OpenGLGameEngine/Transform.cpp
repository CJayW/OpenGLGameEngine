#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Transform::Transform() {
	position = glm::vec3(0);
	rotation = glm::quat(glm::vec3(0, 0, 0));
	scale = glm::vec3(0);
}

Transform::Transform(std::string message) {
	Transform();
}

Transform::~Transform() {

}

void Transform::rotate(glm::vec3 euler) {
	glm::quat eulerQuat = glm::quat(euler / (180 / 3.1415972f));
	rotation = rotation * glm::inverse(rotation) * eulerQuat * rotation;
}