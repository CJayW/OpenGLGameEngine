#pragma once

#include <glad\glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
public:
	unsigned int ID;
	//Reads and builds the shaders
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	//Activates or deactivates the shader
	void use();

	//Uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};