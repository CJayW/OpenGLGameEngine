#include "GameObject.h"

#include <iostream>
#include "Transform.h"

#include "imGUI/imgui.h"
#include "EditorMode.h"
#include "GameObjectManager.h"

unsigned int GameObject::nextCompID = 0;

GameObject::GameObject() {
	transform = addComponent<Transform>();
	componentDetailsOpen = false;
}

GameObject::~GameObject() {
	int total = components.size();
	for (int i = 0; i < total; i++) {
		delete components[i];
	}
	for (int i = 0; (size_t)i < children.size(); i++) {
		delete children[i];
	}
	std::cout << "Decon: " << Name << std::endl;
}

void GameObject::Update(double deltaTime) {
	for (auto component : components) {
		component->Update(deltaTime);
	}

	for (auto obj : children) {
		obj->Update(deltaTime);
	}
}

void GameObject::Render() {
	for (auto obj : children) {
		obj->Render();
	}

	for (auto component : components) {
		component->Render();
	}
}

void GameObject::RenderUIEditor(std::string prefix) {

	if (componentDetailsOpen) {

		ImGui::End();
		ImGui::Begin((std::string("Object Details##") + std::to_string(ID)).c_str(), &componentDetailsOpen);


		static char EditorName[20];


		if (ImGui::InputText((std::string("##") + std::to_string(ID)).c_str(), EditorName, sizeof(EditorName),ImGuiInputTextFlags_EnterReturnsTrue)) {
			Name = EditorName;
		}

		ImGui::Text(transform->DisplayName.c_str());
		transform->RenderUIEditor();
		ImGui::Separator();

		for(int i = 1; (size_t)i < components.size(); i++) {
			ImGui::Text(components[i]->DisplayName.c_str());
			ImGui::SameLine();
	
			if (ImGui::Button((std::string("X##") + std::to_string(components[i]->ID)).c_str())) {
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
	
	ImGui::Text(prefix.c_str());
	ImGui::SameLine();
	if(ImGui::Button((Name + std::string("##") + std::to_string(ID)).c_str())) {
		componentDetailsOpen = !componentDetailsOpen;
		if (componentDetailsOpen) {
			for (auto comp : components)
			{
				comp->OpenUIEditor();
			}
		}
	}

	ImGui::SameLine();
	ImGui::Text("   ");
	ImGui::SameLine();
	if (ImGui::Button((std::string("X##") + std::to_string(ID)).c_str())) {
		GameObjectManager::DestroyObject(this);
		return;
	}

	ImGui::SameLine();
	ImGui::Text(" ");
	ImGui::SameLine();
	if (ImGui::Button((std::string("+##") + std::to_string(ID)).c_str())) {
		GameObjectManager::Instantiate(this);
	}


	for (auto comp : components) {
		ImGui::Text(prefix.c_str());
		ImGui::SameLine();
		ImGui::Text(comp->DisplayName.c_str());
	}

	for (auto child : children) {
		child->RenderUIEditor(prefix + "    ");
	}

}