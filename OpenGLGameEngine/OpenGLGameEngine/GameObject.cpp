#include "GameObject.h"

#include <iostream>
#include "Transform.h"

#include "imGUI/imgui.h"
#include "EditorMode.h"
#include "GameObjectManager.h"

GameObject::GameObject() {
	transform = addComponent<Transform>();
	componentDetailsOpen = false;
}

GameObject::~GameObject() {
	int total = components.size();
	for (int i = 0; i < total; i++) {
		delete components[i];
	}
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

		ImGui::Text(transform->DisplayName.c_str());
		transform->RenderUIEditor();
		ImGui::Separator();

		for(int i = 1; i < components.size(); i++) {
			ImGui::Text(components[i]->DisplayName.c_str());
			ImGui::SameLine();
			
			if (ImGui::Button((std::string("X##") + components[i]->DisplayName).c_str())) {

				removeComponentByReferance(components[i]);
			} else {
				components[i]->RenderUIEditor();
				ImGui::Separator();
			}
		}

		ImGui::NewLine();

		if(ImGui::Button("Add Component")) {
			EditorMode::OpenAddComponent(this);

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

	ImGui::SameLine();
	ImGui::Text("  ");
	ImGui::SameLine();
	if (ImGui::Button((std::string("X##") + Name).c_str())) {
		GameObjectManager::DestroyObject(this);
	}

	for (auto comp : components) {
		ImGui::Text(comp->DisplayName.c_str());
	}

}