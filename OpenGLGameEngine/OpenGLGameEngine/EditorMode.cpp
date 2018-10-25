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
EditorMode::EditorMode()
{
}


EditorMode::~EditorMode()
{
}

bool EditorMode::EditorModeActive = true;

bool EditorMode::addingComponent;
GameObject* EditorMode::addComponentObject;

void EditorMode::Init() {
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(Game::window, true);

	ImGui::StyleColorsDark();

}

void EditorMode::Update() {

}

void EditorMode::Render() {

	bool test;

	glm::vec4 col(0);

	ImGui_ImplGlfwGL3_NewFrame();
	{
		ImGui::Begin("hierarchy");

		if (ImGui::Button("New GameObject")) {

			GameObject* obj = GameObjectManager::Instantiate();

			int nameIndex = 1;

			while (GameObjectManager::GetObjectByName(std::string("New Object") + std::to_string(nameIndex)) != nullptr) {
				nameIndex++;
			}

			obj->Name = std::string("New Object") + std::to_string(nameIndex);
		}

		ImGui::Separator();

		for (int i = 0; i < Game::GameObjects.size(); i++) {
			Game::GameObjects[i]->RenderUIEditor();
		}
		
		ImGui::End();

		if (addingComponent) {
			if (addComponentObject->components.capacity() == 0) {
				
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

	}

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

}

void EditorMode::ChangeEditorMode(bool newMode)
{
	if (EditorModeActive) {


	} else {


	}
}

void EditorMode::OpenAddComponent(GameObject * obj) {

	addingComponent = true;
	addComponentObject = obj;
}
