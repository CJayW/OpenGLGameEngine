#include "Shader.h"

#include "Light.h"
#include <string>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>

Shader::Shader(const std::string vertexPath, const std::string fragmentPath) {

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//open files
		vShaderFile.open("Resources/Shaders/" + vertexPath);
		fShaderFile.open("Resources/Shaders/" + fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//close file handlers
		vShaderFile.close();
		fShaderFile.close();
		//convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};


	//fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	//shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

}

void Shader::use() {
	glUseProgram(ID);

	for (int i = 0; (size_t)i < Light::directionalLights.size(); i++) {
		if (i >= 10) {
			break;
		}
		std::string iStr = std::to_string(i);

		setVec3("dirLights[" + iStr + "].direction", Light::directionalLights[i]->transform->rotation * glm::vec3(1, 0, 0));
		setVec3("dirLights[" + iStr + "].ambient", Light::directionalLights[i]->ambient);
		setVec3("dirLights[" + iStr + "].diffuse", Light::directionalLights[i]->diffuse);
	}

	for (int i = 0; (size_t)i < Light::pointLights.size(); i++) {
		if (i >= 10) {
			break;
		}
		std::string iStr = std::to_string(i);
		setVec3( "pointLights[" + iStr + "].position", Light::pointLights[i]->transform->position);

		setVec3( "pointLights[" + iStr + "].ambient", Light::pointLights[i]->ambient);
		setVec3( "pointLights[" + iStr + "].diffuse", Light::pointLights[i]->diffuse);

		setFloat("pointLights[" + iStr + "].constant", Light::pointLights[i]->constant);
		setFloat("pointLights[" + iStr + "].linear", Light::pointLights[i]->linear);
		setFloat("pointLights[" + iStr + "].quadratic", Light::pointLights[i]->quadratic);

	}

	for (int i = 0; i < Light::spotLights.size(); i++) {
		if (i >= 10) {
			break;
		}
		std::string iStr = std::to_string(i);

		setVec3("spotLights[" + iStr + "].position", Light::spotLights[i]->transform->position);
		setVec3("spotLights[" + iStr + "].direction", Light::spotLights[i]->transform->rotation * glm::vec3(1,0,0));

		setVec3("spotLights[" + iStr + "].ambient", Light::spotLights[i]->ambient);
		setVec3("spotLights[" + iStr + "].diffuse", Light::spotLights[i]->diffuse);

		setFloat("spotLights[" + iStr + "].constant", Light::spotLights[i]->constant);
		setFloat("spotLights[" + iStr + "].linear", Light::spotLights[i]->linear);
		setFloat("spotLights[" + iStr + "].quadratic", Light::spotLights[i]->quadratic);

		setFloat("spotLights[" + iStr + "].cutOff", glm::cos(glm::radians(Light::spotLights[i]->width * (1 - Light::spotLights[i]->blur))));
		setFloat("spotLights[" + iStr + "].outerCutOff", glm::cos(glm::radians(Light::spotLights[i]->width)));
	}
}