#pragma once

#include "EditorCamera.h"
#include <vector>
#include <string>
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

	static glm::vec3 clearColor;

private:
	static bool cursorShouldBeHidden;
	static float playingTimeScale;

	static char saveFileNameBuff[32];
	static std::string nameErrorMessages;
	static std::string saveFileNameString;
};