#include "Game.h"
#include "Input.h"
#include "GameObjectManager.h"

#include <string>

//components
#include "Transform.h"
#include "MeshRenderer.h"
#include "TestMove.h"
#include "CameraMovement.h"
#include "Shader.h"


#include <glm/gtc/matrix_transform.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int Game::width;
int Game::height;
bool Game::Running;
std::vector<GameObject*> Game::GameObjects;
GLFWwindow* Game::window;

Game::Game() { }

Game::~Game() { }

void Game::Init(int Width, int Height, bool FullScreen, const char* Title) {
	width = Width;
	height = Height;
	Running = true;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

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

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	Camera::UpdateCameraProjection();
}

void Game::Start() {
	GameObject* obj = GameObjectManager::Instantiate();
	camera = obj->addComponent<Camera>();
	camera->UpdateCameraView();
	obj->addComponent<CameraMovement>();

	obj = GameObjectManager::Instantiate();
	obj->addComponent<MeshRenderer>();
	obj->addComponent<TestMove>();

	obj = GameObjectManager::Instantiate();
	obj->addComponent<MeshRenderer>();
	obj->transform->position.z = -3;
	obj->transform->position.x = -3;

	obj = GameObjectManager::Instantiate();
	obj->addComponent<MeshRenderer>();
	obj->transform->position.z = 3;
	obj->transform->position.x = -3;

	obj = GameObjectManager::Instantiate();
	obj->addComponent<MeshRenderer>();
	obj->transform->position.x = -6;
}

void Game::Update(double deltaTime) {

	for (auto gameObject : GameObjects) {
		gameObject->Update(deltaTime);
	}
}

void Game::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto gameObject : GameObjects) {
		gameObject->Render();
	}
	glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	Game::width = width;
	Game::height = height;

	Camera::UpdateCameraProjection();
}