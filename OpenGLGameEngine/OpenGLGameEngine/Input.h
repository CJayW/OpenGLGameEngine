#pragma once
#include "Game.h"

#include <iostream>

#define InputAxisMouseX 0
#define InputAxisMouseY 1

#define InputAxisCount 2

class Input {
public:
	Input();
	~Input();

	void ProcessInput();


	static bool getKey(int key) {
		return   ImGui::IsAnyItemActive() ? false : keysDown[key];
	}
	static bool getKeyDown(int key) {
		return ImGui::IsAnyItemActive() ? false : keysPressed[key];
	}
	static bool getKeyUp(int key) {
		return ImGui::IsAnyItemActive() ? false : keysReleased[key];
	}
	static double getAxis(int Axis) {
		return ImGui::IsAnyItemActive() ? 0 : InputAxisValues[Axis];
	}

	static void updateMousePos(GLFWwindow* window, double xpos, double ypos);

	static void SwitchCursorState(bool displayMouse);

	static bool mouseHidden;

private:
	//used to check if the mouse pos has already been checked - prevents large axis jumps at the start
	static bool firstMouse;

	void checkKey(unsigned int key);

	static double InputAxisValues[InputAxisCount];

	static bool keysDown[GLFW_KEY_LAST];
	static bool keysPressed[GLFW_KEY_LAST];
	static bool keysReleased[GLFW_KEY_LAST];

	static double mouseX, mouseY;
};