#include "TestMove.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Transform.h"
TestMove::TestMove()
{

}


TestMove::~TestMove()
{

}

void TestMove::Update(double deltaTime) {
	std::cout << transform->position.x << std::endl;
}