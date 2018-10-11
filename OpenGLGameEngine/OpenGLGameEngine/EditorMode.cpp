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
		static float f = 0.0f;
		static int counter = 0;
		ImGui::Text("message");									// Display some text (you can use a format string too)

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
		ImGui::ColorEdit3("clear color", glm::value_ptr(col)); // Edit 3 floats representing a color

		ImGui::Checkbox("Demo Window", &test);      // Edit bools storing our windows open/close state

		if (ImGui::Button("Button")) {                         // Buttons return true when clicked (NB: most widgets return true when edited/activated)
			glClearColor(col.x, col.y, col.z, col.a);
		}

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

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