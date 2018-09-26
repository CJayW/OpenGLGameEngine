#pragma once
#include "Game.h"

#include <iostream>


class Input {
public:
	Input();
	~Input();

	void ProcessInput();

	static bool getKey(int key) {
		return keysDown[key];
	}
	static bool getKeyDown(int key) {
		return keysPressed[key];
	}
	static bool getKeyUp(int key) {
		return keysReleased[key];
	}

	static void updateMousePos(GLFWwindow* window, double xpos, double ypos);
private:
	void checkKey(unsigned int key);

	static bool keysDown[GLFW_KEY_LAST];
	static bool keysPressed[GLFW_KEY_LAST];
	static bool keysReleased[GLFW_KEY_LAST];

	static double mouseX, mouseY;
};