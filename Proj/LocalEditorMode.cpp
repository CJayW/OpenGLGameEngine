#include "LocalEditorMode.h"
#include "F:/OpenGLGameEngine/OpenGLGameEngine/OpenGLGameEngine/EditorMode.h"

#include "move.h" 
#include "PlayerMovement.h" 
//IncludeHere
//^ Needed to auto add classes

LocalEditorMode::LocalEditorMode() {
}


LocalEditorMode::~LocalEditorMode() {
}

#define editorAddComponent(ComponentType, DisplayName) \
if (ImGui::Button(DisplayName)) {\
EditorMode::addComponentObject->addComponent<ComponentType>();\
} else

void LocalEditorMode::AddComponent() {
	
	editorAddComponent(move, "Move"); 
	editorAddComponent(PlayerMovement, "Player Move"); 
//AddNewComponentsHere
	//^ Needed to auto add classes
}