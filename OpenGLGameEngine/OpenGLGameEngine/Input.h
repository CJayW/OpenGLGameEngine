#pragma once
//#include <GLFW/glfw3.h>
#include <iostream>

class Input {
public:
	Input();
	~Input();

	static void Init();

	static void ProcessInput();
};