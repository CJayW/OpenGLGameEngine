#include "Input.h"
#include <functional>

double Input::mouseX;
double Input::mouseY;

bool Input::firstMouse;

double Input::InputAxisValues[InputAxisCount];

bool Input::keysDown[GLFW_KEY_LAST];
bool Input::keysPressed[GLFW_KEY_LAST];
bool Input::keysReleased[GLFW_KEY_LAST];

bool Input::cursorHidden = false;
bool Input::WindowMinimized = false;

bool Input::BlockFurtherInputs;

Input::Input() {
	glfwSetCursorPosCallback(Game::window, Input::updateMousePos);
	glfwSetScrollCallback(Game::window, Input::updateScrollInput);
	glfwSetWindowIconifyCallback(Game::window, Input::updateIconifyState);
	SetCursorState(false);
	for (int i = 0; i < GLFW_KEY_MENU; i++) {
		keysDown[i] = false;
		keysPressed[i] = false;
		keysReleased[i] = false;
	}

	firstMouse = true;
}

Input::~Input() {
}

#include "EditorDebug.h"

void Input::ProcessInput() {

	for (int i = 0; i < InputAxisCount; i++) {
		InputAxisValues[i] = 0;
	}

	glfwPollEvents();
	//The fist call after ^ causes a crash if the window is minimized
	
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
	BlockFurtherInputs = false;
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

void Input::updateScrollInput(GLFWwindow * window, double X, double Y) {
	InputAxisValues[InputMouseScroll] = Y;

	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += (float)X;
	io.MouseWheel += (float)Y;
}

void Input::updateIconifyState(GLFWwindow * window, int open) {
	WindowMinimized = (bool)open;
}

void Input::SetCursorState(bool displayMouse) {
	cursorHidden = !displayMouse;

	if (displayMouse) {
		glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

}