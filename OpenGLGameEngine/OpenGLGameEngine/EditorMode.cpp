#include "EditorMode.h"
#include  "Game.h"
#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw_gl3.h"
#include "GameObject.h"

#include "Rigidbody.h"

#include "GameObjectManager.h"

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
			if (!addComponentObject) {
				
				addingComponent = false;

			} else {
				ImGui::Begin("Add Component", &addingComponent);

				ImGui::Text((std::string("Adding Component To:  ") + addComponentObject->Name).c_str());

				if (ImGui::Button("RigidBody")) {

					addComponentObject->addComponent<Rigidbody>();
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
