#include "EditorMode.h"
#include  "Game.h"
#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw_gl3.h"
#include "GameObject.h"
#include "GameObjectManager.h"

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

EditorMode::EditorMode()
{
}


EditorMode::~EditorMode()
{
	delete editorCamera;
	editorCamera = NULL;
}

bool EditorMode::EditorModeActive = false;
bool EditorMode::paused = false;

EditorCamera* EditorMode::editorCamera;

bool EditorMode::cursorShouldBeHidden;
float EditorMode::playingTimeScale;

bool EditorMode::addingComponent;
GameObject* EditorMode::addComponentObject;

void EditorMode::Init() {
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(Game::window, true);

	ImGui::StyleColorsDark();

	editorCamera = new EditorCamera();
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

void EditorMode::Render() {
	if (!EditorModeActive)
		return;

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

			if (ImGui::Button("RigidBody")) {
				addComponentObject->addComponent<Rigidbody>();
			} else if (ImGui::Button("Camera")) {
				addComponentObject->addComponent<Camera>();
			} else if (ImGui::Button("Mesh Renderer")) {
				addComponentObject->addComponent<MeshRenderer>();
			} else if (ImGui::Button("Icon Renderer")) {
				addComponentObject->addComponent<IconRenderer>();
			} else if (ImGui::Button("Directional Light")) {
				addComponentObject->addComponent<DirectionalLight>();
			} else if (ImGui::Button("Point Light")) {
				addComponentObject->addComponent<PointLight>();
			} else if (ImGui::Button("Spot Light")) {
				addComponentObject->addComponent<SpotLight>();
			} else if (ImGui::Button("CameraMovement")) {
				addComponentObject->addComponent<CameraMovement>();
			} else if (ImGui::Button("Test Movement")) {
				addComponentObject->addComponent<TestMove>();
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

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorMode::ChangeEditorMode(bool active)
{
	if (!active) {
		Input::SetCursorState(!cursorShouldBeHidden);
		Time::timeScale = playingTimeScale;
		paused = false;
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