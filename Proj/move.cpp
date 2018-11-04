#include "move.h"

std::string move::name = "move";

move::move() {
}

move::move(std::string _params) {
	std::vector<std::string> params = LevelFileManager::splitBy(_params, ',');
	//split params
}

move::~move() {
}

std::string move::ToSaveString() {
	std::string str = name + "(";
	
	return str;
}

void move::Start() {
	DisplayName = name;
	EditorDebug::Log("Move Added");
}

void move::Render() {
}

void move::Update(double deltaTime) {
}

void move::RenderUIEditor() {
}
