#include "Game.h"
#include "Input.h"
#include "GameObjectManager.h"

#include <string>

//components
#include "Transform.h"
#include "MeshRenderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Game::Game() { }


Game::~Game() { }

GLFWwindow* Game::window;
int Game::width;
int Game::height;
bool Game::Running;

std::vector<GameObject*> Game::GameObjects;

void Game::Init(int Width, int Height, bool FullScreen, const char* Title) {
	width = Width;
	height = Height;
	Running = true;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, Title, NULL, NULL);
	if (window == NULL) {
		std::cout << "Error: Window Not Created" << std::endl;
		glfwTerminate();
		Running = false;
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	Input::Init();


	GameObject* obj = GameObjectManager::Instantiate();

}

void Game::Update(double deltaTime) {
	for (auto gameObject : GameObjects) {
		gameObject->Update(deltaTime);
	}
}

void Game::Render() {
	for (auto gameObject : GameObjects) {
		gameObject->Render();
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	Game::width = width;
	Game::height = height;
}