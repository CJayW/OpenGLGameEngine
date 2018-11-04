#pragma once
#include "Include.h"

class #ClassName : public Component {
public:

	static std::string name;

	#ClassName();
	#ClassName(std::string params);
	~#ClassName();

	std::string ToSaveString() override;

	void Start() override;
	void Render() override;
	void Update(double deltaTime) override;
	

	//Editor
	void RenderUIEditor() override;
};