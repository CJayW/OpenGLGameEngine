#include "Transform.h"


Transform::Transform() {
	position = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(0);
}

Transform::Transform(std::string message) {
	//parse string

}

Transform::~Transform() {
}
