#include "PlayerMovement.h"

std::string PlayerMovement::name = "PlayerMovement";

PlayerMovement::PlayerMovement() {
}

PlayerMovement::PlayerMovement(std::string _params) {
	std::vector<std::string> params = LevelFileManager::splitBy(_params, ',');
	//split params
}

PlayerMovement::~PlayerMovement() {
}

std::string PlayerMovement::ToSaveString() {
	std::string str = name + "(";
	
	return str;
}

void PlayerMovement::Start() {
	DisplayName = name;
}

void PlayerMovement::Render() {
}

void PlayerMovement::Update(double deltaTime) {
}

void PlayerMovement::RenderUIEditor() {
}
