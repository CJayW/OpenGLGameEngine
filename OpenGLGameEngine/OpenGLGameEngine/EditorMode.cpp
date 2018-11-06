#include "EditorMode.h"
#include  "Game.h"
#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw_gl3.h"
#include "GameObject.h"
#include "GameObjectManager.h"

//Components
#include "Rigidbody.h"
#include "MeshRenderer.h"
#include "IconRenderer.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "CameraMovement.h"
#include "TestMove.h"

#include "Time.h"
#include "Input.h"
#include "EditorDebug.h"
#include "Shader.h"

#include "LevelFileManager.h"

#include <fstream>


//Include Project Location
#include "E:/OpenGLGameEngine/Proj/LocalEditorMode.h"
//^ Needed for the programming assistant


EditorMode::EditorMode()
{
}


EditorMode::~EditorMode()
{
	delete editorCamera;
	editorCamera = NULL;
}

bool EditorMode::EditorModeActive = true;
bool EditorMode::paused = true;

EditorCamera* EditorMode::editorCamera;

bool EditorMode::cursorShouldBeHidden;
float EditorMode::playingTimeScale;

bool EditorMode::addingComponent;
GameObject* EditorMode::addComponentObject;

glm::vec3 EditorMode::clearColor;

char EditorMode::saveFileNameBuff[32];
std::string EditorMode::nameErrorMessages;
std::string EditorMode::saveFileNameString;

void EditorMode::Init() {
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(Game::window, true);

	ImGui::StyleColorsDark();

	editorCamera = new EditorCamera();

	cursorShouldBeHidden = true;
	playingTimeScale = 1;
}

void EditorMode::Update() {
	if (Input::getKeyDown(GLFW_KEY_GRAVE_ACCENT)) { // `
		ChangeEditorMode(!EditorModeActive);
	}

	if (EditorModeActive) {
		editorCamera->Update();
		Input::BlockFurtherInputs = true;
	}
}

#define editorAddComponent(ComponentType, DisplayName) \
if (ImGui::Button(DisplayName)) {\
addComponentObject->addComponent<ComponentType>();\
} else

void EditorMode::Render() {
	ImGui_ImplGlfwGL3_NewFrame();

	//GameObjects
	{
		ImGui::Begin("hierarchy");

		if (ImGui::Button("New GameObject")) {

			GameObject* obj = GameObjectManager::Instantiate();
		}

		ImGui::Separator();

		for (int i = 0; (size_t)i < Game::GameObjects.size(); i++) {
			Game::GameObjects[i]->RenderUIEditor("");
		}
		
		ImGui::End();
	}

	
	if (addingComponent) {
		if (addComponentObject->components.size() == 0) {

			addingComponent = false;
		} else {
			ImGui::Begin("Add Component", &addingComponent);

			ImGui::Text((std::string("Adding Component To:  ") + addComponentObject->Name).c_str());

			editorAddComponent(Rigidbody, "Rigidbody");
			editorAddComponent(Camera, "Camera");
			editorAddComponent(MeshRenderer, "Mesh Renderer");
			editorAddComponent(IconRenderer, "Icon Renderer");
			editorAddComponent(DirectionalLight, "Directional Light");
			editorAddComponent(PointLight, "Point Light");
			editorAddComponent(SpotLight, "Spot Light");
			editorAddComponent(CameraMovement, "Camera Movement");
			editorAddComponent(TestMove, "Test Movement");
			{
				LocalEditorMode::AddComponent();
			}

			ImGui::End();
		}
	}
	
	//Time
	{
		ImGui::Begin("Time");

		ImGui::DragFloat("TimeScale", &Time::timeScale, 0.1f, 0, 5);
		ImGui::Checkbox("Paused", &paused);
		ImGui::End();
	}

	//globalLighting
	{
		ImGui::Begin("Global Lighting");
		if (ImGui::ColorEdit3("Ambient", glm::value_ptr(Light::Ambient))) {
			Light::UpdateAmbient();
		}

		if (ImGui::ColorEdit3("Clear Colour", glm::value_ptr(Light::ClearColour))){
			Light::UpdateClearColour();
		}

		ImGui::End();
	}
	{
		ImGui::Begin("Level Manager");

		if (ImGui::InputText("LevelName", saveFileNameBuff, 32)) {
			saveFileNameString = std::string(saveFileNameBuff);

			if (LevelFileManager::checkLevelName(saveFileNameString)) {
				nameErrorMessages = "Level File Found";
			} else {
				nameErrorMessages = "No Level File";
			}
		}

		if (ImGui::Button("Save")) {			
			if (saveFileNameString != "") {
				LevelFileManager::saveLevel(saveFileNameString);
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("Load")) {
			if (LevelFileManager::checkLevelName(saveFileNameString)) {
				LevelFileManager::loadLevel(saveFileNameString);

			}
		}
		
		ImGui::Text(nameErrorMessages.c_str());

		ImGui::End();
	}

	EditorDebug::Render();

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorMode::ChangeEditorMode(bool active)
{
	if (!active) {
		Input::SetCursorState(!cursorShouldBeHidden);
		Time::timeScale = playingTimeScale;
		paused = false;

		if (Renderer::CurrentShaderProgram) {
			Renderer::CurrentShaderProgram->setMat4("view", Camera::viewMatrix);
		}

	} else {
		cursorShouldBeHidden = Input::cursorHidden;
		Input::SetCursorState(true);
		playingTimeScale = Time::timeScale;
		paused = true;
	}

	EditorModeActive = active;
}

void EditorMode::OpenAddComponent(GameObject * obj) {

	addingComponent = true;
	addComponentObject = obj;
}

//End Of File