#include "Game.h"
#include "Input.h"
#include "GameObjectManager.h"
#include "LevelFileManager.h"

#include <string>

//components
#include "Transform.h"
#include "MeshRenderer.h"
#include "TestMove.h"
#include "CameraMovement.h"
#include "Shader.h"
#include "IconRenderer.h"

#include "EditorMode.h"
#include "Time.h"

#include "EditorDebug.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int Game::width;
int Game::height;
bool Game::Running;
std::vector<GameObject*> Game::GameObjects;
GLFWwindow* Game::window;
Camera* Game::camera;

Game::Game() { }

Game::~Game() { }

void Game::Init(int Width, int Height, bool FullScreen, const char* Title) {

	Running = true;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (FullScreen) {
		glfwWindowHint(GLFW_MAXIMIZED, 1);
	}

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	window = glfwCreateWindow(Width, Height, Title, NULL, NULL);
	if (window == NULL) {
		std::cout << "Error: Window Not Created" << std::endl;
		glfwTerminate();
		Running = false;
		return;
	}

	glfwGetWindowSize(window, &width, &height);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	glfwSwapInterval(0); // <-- removes the FPS Cap


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	EditorMode::Init();

	Camera::UpdateCameraProjection();
}

void Game::Start() {
	LevelFileManager::loadLevel();

	return;

	GameObject* obj = GameObjectManager::Instantiate();
	obj->addComponent<IconRenderer>("pointLightIcon.jpg");
	obj->Name = "Parent Obj";

	obj = GameObjectManager::Instantiate(obj);
	obj->Name = "Child OBJ";
	obj->addComponent<MeshRenderer>("house.ply");

	obj = GameObjectManager::Instantiate();
	obj->addComponent<IconRenderer>("pointLightIcon.jpg");
	obj->Name = "Parent Obj 2";

	obj = GameObjectManager::Instantiate(obj);
	obj->Name = "Child OBJ 2";
	obj->addComponent<MeshRenderer>("house.ply");

	GameObjectManager::Instantiate(GameObjectManager::GetObjectByName("Player"));

}

void Game::Update(double deltaTime) {

	EditorMode::Update();
	
	if (!EditorMode::paused) {
		for (auto gameObject : GameObjects) {
			gameObject->Update(deltaTime);
		}
	}
}

void Game::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (EditorMode::EditorModeActive) {
		EditorMode::editorCamera->UpdateCameraView();
	} else if(camera != NULL){
		camera->UpdateCameraView();
	}

	for (auto gameObject : GameObjects) {
		gameObject->Render();
	}
	if (EditorMode::EditorModeActive) 
		EditorMode::Render();

	glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	Game::width = width;
	Game::height = height;

	Camera::UpdateCameraProjection();
}