#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	static Camera* camera;

	static double getTime() {
		return glfwGetTime();
	}
};

