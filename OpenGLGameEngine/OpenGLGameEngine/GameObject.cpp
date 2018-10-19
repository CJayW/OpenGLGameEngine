#include "GameObject.h"

#include <iostream>
#include "Transform.h"

#include "imGUI/imgui.h"

GameObject::GameObject() {
	transform = addComponent<Transform>();
	componentDetailsOpen = false;
}

GameObject::~GameObject() {

}

void GameObject::Start() {
	for (auto component : components) {
		component->Start();
	}
}

void GameObject::Update(double deltaTime) {

	for (auto component : components) {
		component->Update(deltaTime);
	}
}

void GameObject::Render() {

	for (auto component : components) {
		component->Render();
	}
}

void GameObject::RenderUIEditor() {

	if (componentDetailsOpen) {

		ImGui::End();

		bool open;
		ImGui::Begin(Name.c_str(), &open);
		componentDetailsOpen = open;

		for (auto comp : components) {
			ImGui::Text(comp->DisplayName.c_str());

			comp->RenderUIEditor();
			ImGui::Separator();
		}

		ImGui::End();

		ImGui::Begin("hierarchy");
	}

	if(ImGui::Button(Name.c_str())) {
		componentDetailsOpen = !componentDetailsOpen;
		if (componentDetailsOpen) {
			for (auto comp : components)
			{
				comp->OpenUIEditor();
			}
		}
	}

	for (auto comp : components) {
		ImGui::Text(comp->DisplayName.c_str());
	}
}