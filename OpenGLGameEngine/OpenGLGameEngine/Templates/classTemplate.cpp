#include "#ClassName.h"

std::string #ClassName::name = "#ClassName";

#ClassName::#ClassName() {
}

#ClassName::#ClassName(std::string _params) {
	std::vector<std::string> params = LevelFileManager::splitBy(_params, ',');
	//split params
}

#ClassName::~#ClassName() {
}

std::string #ClassName::ToSaveString() {
	std::string str = name + "(";
	
	return str;
}

void #ClassName::Start() {
	DisplayName = name;
}

void #ClassName::Render() {
}

void #ClassName::Update(double deltaTime) {
}

void #ClassName::RenderUIEditor() {
}
