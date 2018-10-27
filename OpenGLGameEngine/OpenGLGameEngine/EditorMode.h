#pragma once

#include "EditorCamera.h"

class GameObject;

class EditorMode
{
public:
	EditorMode();
	~EditorMode();

	static void Init();
	static void Update();
	static void Render();

	static void ChangeEditorMode(bool Active);
	static bool EditorModeActive;

	static bool paused;

	static EditorCamera* editorCamera;
		
	static void OpenAddComponent(GameObject* obj);
	static bool addingComponent;
	static GameObject* addComponentObject;

private:
	static bool cursorShouldBeHidden;
	static float playingTimeScale;
};