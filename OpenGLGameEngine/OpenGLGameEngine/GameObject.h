#pragma once

#include <vector>
#include "Component.h"
class Transform;

class GameObject {
public:
	GameObject();
	~GameObject();

	std::vector<Component*> components;

	void Start();
	void Update(double deltaTime);
	void Render();
	

	Transform* transform;
	
	//Editor
	void RenderUIEditor();

	std::string Name;
	bool componentDetailsOpen;
#pragma region components 

	template <typename componentType, typename... ArgsT>
	componentType* addComponent(ArgsT&&... Args) {
		componentType* comp = new componentType(std::forward<ArgsT>(Args)...);
		comp->gameObject = this;
		comp->transform = transform;
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
		for (int i = 0; (size_t)i < components.size(); i++){ 
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

		components.erase(components.begin() + i);
	}

	void removeComponentByReferance(Component* comp) {
		for (int i = 0; (size_t)i < components.size(); i++) {
			if (components[i] == comp) {

				Component* comp = components[i];

				delete comp;

				components.erase(components.begin() + i);
			}
		}
	}

#pragma endregion
};

