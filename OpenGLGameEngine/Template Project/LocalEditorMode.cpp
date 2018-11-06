#include "LocalEditorMode.h"
#include "Editor Location/EditorMode.h"
 
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
	
//AddNewComponentsHere
	//^ Needed to auto add classes
}