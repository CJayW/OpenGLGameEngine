#include "EditorMode.h"
#include  "Game.h"
#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw_gl3.h"

EditorMode::EditorMode()
{
}


EditorMode::~EditorMode()
{
}

bool EditorMode::EditorModeActive = true;

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

		for (int i = 0; i < Game::GameObjects.size(); i++) {
			Game::GameObjects[i]->RenderUIEditor();
		}

		ImGui::End();
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