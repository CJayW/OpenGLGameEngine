#include "GameObject.h"

#include <iostream>
#include "Transform.h"
GameObject::GameObject() {
	transform = addComponent<Transform>();
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