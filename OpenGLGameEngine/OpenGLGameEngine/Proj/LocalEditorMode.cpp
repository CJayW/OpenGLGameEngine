#include "LocalEditorMode.h"
#include "../EditorMode.h"

#include "move.h" 
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
//AddNewComponentsHere
	//^ Needed to auto add classes
}