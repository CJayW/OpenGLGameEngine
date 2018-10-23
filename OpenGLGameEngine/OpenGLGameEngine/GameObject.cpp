#include "GameObject.h"

#include <iostream>
#include "Transform.h"

#include "imGUI/imgui.h"
#include "EditorMode.h"

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
			ImGui::SameLine();
			
			if (ImGui::Button((std::string("X##") + comp->DisplayName).c_str())) {
				std::cout << comp->DisplayName << std::endl;

				removeComponentByReferance(comp);
			} else {
				comp->RenderUIEditor();
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
		std::cout << "Remove Object:  " << Name << std::endl;
		//TODO Implament this
	}

	for (auto comp : components) {
		ImGui::Text(comp->DisplayName.c_str());
	}

}