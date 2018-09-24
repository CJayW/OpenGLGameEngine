#include "Input.h"
#include "Game.h"

void mouseMove(GLFWwindow* window, double xpos, double ypos);

Input::Input() {
}

Input::~Input() {
}

void Input::Init() {
	glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(Game::window, mouseMove);
}

void Input::ProcessInput() {
	glfwPollEvents();

	if (glfwWindowShouldClose(Game::window)) {
		Game::Running = false;
	}

}

void mouseMove(GLFWwindow* window, double xpos, double ypos) {
	//std::cout << xpos << " : " << ypos << std::endl;
}
