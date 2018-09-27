#pragma once

#include "OpenGLInclude.h"

#include <vector>
#include <iostream>
#include "GameObject.h"
#include "Camera.h"

class Game {
public:
	Game();
	~Game();
	void Init(int width, int height, bool fullscreen, const char* title);
	void Start();

	void Update(double deltaTime);

	void Render();

	static bool Running;

	static int width;
	static int height;
	static GLFWwindow* window;
	static std::vector<GameObject*> GameObjects;

	Camera* camera;

	static double getTime() {
		return glfwGetTime();
	}
};

