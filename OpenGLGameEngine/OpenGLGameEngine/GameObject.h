#pragma once

#include <vector>
#include "Component.h"

class GameObject {
public:
	GameObject();
	~GameObject();

	std::vector<Component*> components;

	void Start();
	void Update(double deltaTime);
	void Render();

	template <typename componentType, typename... ArgsT>
	componentType* addComponent(ArgsT&&... Args) {
		componentType* comp = new componentType(std::forward<ArgsT>(Args)...);
		comp->Start();
		components.push_back(comp);
		return comp;
	};

	
	template <typename componentType>
	componentType* getComponent() {
		for (auto component : components) {
			if (componentType* comp = dynamic_cast<componentType*>(component)) {
				return comp;
			}
		}
		return nullptr;
	}
	
	template <typename componentType>
	int getComponentByIndex() {
		for (int i = 0; i < components.size(); i++){ 
			if (componentType* comp = dynamic_cast<componentType*>(components[i])) {
				return i;
			}
		}
		return -1;
	}

	template<typename componentType>
	void removeComponent() {
		int i = getComponentByIndex<componentType>();
		Component* comp = components[i];
		delete dynamic_cast<componentType*>(comp);

		components.erase(components.begin() + i);
	}
};

