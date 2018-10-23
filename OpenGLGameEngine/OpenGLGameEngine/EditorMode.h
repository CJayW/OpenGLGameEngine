#pragma once

#include "Camera.h"

class GameObject;

class EditorMode
{
public:
	EditorMode();
	~EditorMode();

	static void Init();

	static void Update();

	static void Render();

	static void ChangeEditorMode(bool newMode);

	static bool EditorModeActive;

	static void OpenAddComponent(GameObject* obj);

	static bool addingComponent;
	static GameObject* addComponentObject;
};