#include "Input.h"
#include <functional>

double Input::mouseX;
double Input::mouseY;

bool Input::firstMouse;

double Input::InputAxisValues[InputAxisCount];

bool Input::keysDown[GLFW_KEY_LAST];
bool Input::keysPressed[GLFW_KEY_LAST];
bool Input::keysReleased[GLFW_KEY_LAST];

Input::Input() {
	glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(Game::window, Input::updateMousePos);
	for (int i = 0; i < GLFW_KEY_MENU; i++) {
		keysDown[i] = false;
		keysPressed[i] = false;
		keysReleased[i] = false;
	}

	firstMouse = true;
}

Input::~Input() {
}

void Input::ProcessInput() {
	for (int i = 0; i < InputAxisCount; i++) {
		InputAxisValues[i] = 0;
	}

	glfwPollEvents();

	if (glfwWindowShouldClose(Game::window)) {
		Game::Running = false;
	}
	for (unsigned int i = 32; i < 97; i++) {
		checkKey(i);
	}
	for (unsigned int i = 256; i < 285; i++) {
		checkKey(i);
	}
	for (unsigned int i = 330; i < GLFW_KEY_MENU; i++) {
		checkKey(i);
	}
}

void Input::checkKey(unsigned int key) {

	if (glfwGetKey(Game::window, key) == GLFW_PRESS) {
		if (!keysDown[key]) {
			keysPressed[key] = true;
		}else {
			keysPressed[key] = false;
		}
		keysDown[key] = true;
		keysReleased[key] = false;
	} else if(glfwGetKey(Game::window, key) == GLFW_RELEASE) {
		if (keysDown[key]) {
			keysReleased[key] = true;
		}else {
			keysReleased[key] = false;
		}
		keysDown[key] = false;
		keysPressed[key] = false;
	}
}

void Input::updateMousePos(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		InputAxisValues[InputAxisMouseX] = 0;
		InputAxisValues[InputAxisMouseY] = 0;
		firstMouse = false;
	} else {
		InputAxisValues[InputAxisMouseX] = mouseX - xpos;
		InputAxisValues[InputAxisMouseY] = mouseY - ypos;
	}
	mouseX = xpos;
	mouseY = ypos;
}