#include "Shader.h"
#include <string>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "Transform.h"

#include "Renderer.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>

std::vector<Shader*> Shader::Shaders;

Shader::Shader(const std::string vertexPath, const std::string fragmentPath, bool _useLightData) {
	
	Shaders.push_back(this);

	useLightData = _useLightData;

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

	if (!useLightData) return;

	for (unsigned int i = 0; i < maxLightCount; i++) {
		PointLightsToUpdate.push_back(i);
		DirLightsToUpdate.push_back(i);
		SpotLightsToUpdate.push_back(i);
	}

}

void Shader::use() {
	glUseProgram(ID);

	Renderer::CurrentShaderProgram = this;

	if (!useLightData) return;
	
	for (auto i : DirLightsToUpdate) {
		std::string iStr = std::to_string(i);

		if (Light::directionalLights[i] != nullptr) {
			setVec3("dirLights[" + iStr + "].direction", Light::directionalLights[i]->transform->rotation * glm::vec3(1, 0, 0));
			setVec3("dirLights[" + iStr + "].ambient", Light::directionalLights[i]->ambient);
			setVec3("dirLights[" + iStr + "].diffuse", Light::directionalLights[i]->diffuse);
		} else {
			setVec3("dirLights[" + iStr + "].ambient", glm::vec3(0));
			setVec3("dirLights[" + iStr + "].diffuse", glm::vec3(0));
		}
	}
	DirLightsToUpdate.clear();


	//EditorDebug::Log(std::to_string(PointLightsToUpdate.size()));

	for (auto i : PointLightsToUpdate) {
		std::string iStr = std::to_string(i);

		if (Light::pointLights[i] != nullptr) {
			

			setVec3("pointLights[" + iStr + "].position", Light::pointLights[i]->transform->getPosition());

			setVec3("pointLights[" + iStr + "].ambient", Light::pointLights[i]->ambient);
			setVec3("pointLights[" + iStr + "].diffuse", Light::pointLights[i]->diffuse);

			setFloat("pointLights[" + iStr + "].constant", Light::pointLights[i]->constant);
			setFloat("pointLights[" + iStr + "].linear", Light::pointLights[i]->linear);
			setFloat("pointLights[" + iStr + "].quadratic", Light::pointLights[i]->quadratic);
		} else {
			setVec3("pointLights[" + iStr + "].ambient", glm::vec3(0));
			setVec3("pointLights[" + iStr + "].diffuse", glm::vec3(0));
		}
	}
	PointLightsToUpdate.clear();

	for (auto i : SpotLightsToUpdate) {
		std::string iStr = std::to_string(i);

		if (Light::spotLights[i] != nullptr) {

			setVec3("spotLights[" + iStr + "].position", Light::spotLights[i]->transform->getPosition());
			setVec3("spotLights[" + iStr + "].direction", Light::spotLights[i]->transform->getRotation() * glm::vec3(1, 0, 0));

			setVec3("spotLights[" + iStr + "].ambient", Light::spotLights[i]->ambient);
			setVec3("spotLights[" + iStr + "].diffuse", Light::spotLights[i]->diffuse);

			setFloat("spotLights[" + iStr + "].constant", Light::spotLights[i]->constant);
			setFloat("spotLights[" + iStr + "].linear", Light::spotLights[i]->linear);
			setFloat("spotLights[" + iStr + "].quadratic", Light::spotLights[i]->quadratic);

			setFloat("spotLights[" + iStr + "].cutOff", glm::cos(glm::radians(Light::spotLights[i]->width * (1 - Light::spotLights[i]->blur))));
			setFloat("spotLights[" + iStr + "].outerCutOff", glm::cos(glm::radians(Light::spotLights[i]->width)));
		} else {
			setVec3("spotLights[" + iStr + "].ambient", glm::vec3(0));
			setVec3("spotLights[" + iStr + "].diffuse", glm::vec3(0));
		}
	}
	SpotLightsToUpdate.clear();

#if 0
	if (useLightData) {
		int i;

		for (i = 0; (size_t)i < Light::directionalLights.size(); i++) {
			if (i >= 10) {
				break;
			}
			std::string iStr = std::to_string(i);

			setVec3("dirLights[" + iStr + "].direction", Light::directionalLights[i]->transform->rotation * glm::vec3(1, 0, 0));
			setVec3("dirLights[" + iStr + "].ambient",   Light::directionalLights[i]->ambient);
			setVec3("dirLights[" + iStr + "].diffuse",   Light::directionalLights[i]->diffuse);
		}
		//makes sure to remove the final one 
		//TODO, make it so that you can remove more than one light per refresh
		for(; i < 10; i++){
			std::string iStr = std::to_string(i);;
			setVec3("dirLights[" + iStr + "].ambient", glm::vec3(0));
			setVec3("dirLights[" + iStr + "].diffuse", glm::vec3(0));
		}


		for (i = 0; (size_t)i < Light::pointLights.size(); i++) {
			if (i >= 10) {
				break;
			}
			std::string iStr = std::to_string(i);
			setVec3( "pointLights[" + iStr + "].position",  Light::pointLights[i]->transform->getPosition());
					 
			setVec3( "pointLights[" + iStr + "].ambient",   Light::pointLights[i]->ambient);
			setVec3( "pointLights[" + iStr + "].diffuse",   Light::pointLights[i]->diffuse);

			setFloat("pointLights[" + iStr + "].constant",  Light::pointLights[i]->constant);
			setFloat("pointLights[" + iStr + "].linear",    Light::pointLights[i]->linear);
			setFloat("pointLights[" + iStr + "].quadratic", Light::pointLights[i]->quadratic);
		}

		for (; i < 10; i++) {
			std::string iStr = std::to_string(i);;
			setVec3("pointLights[" + iStr + "].ambient", glm::vec3(0));
			setVec3("pointLights[" + iStr + "].diffuse", glm::vec3(0));
		}

		for (i = 0; (size_t)i < Light::spotLights.size(); i++) {
			if (i >= 10) {
				break;
			}
			std::string iStr = std::to_string(i);

			setVec3("spotLights[" + iStr + "].position",     Light::spotLights[i]->transform->getPosition());
			setVec3("spotLights[" + iStr + "].direction",    Light::spotLights[i]->transform->getRotation() * glm::vec3(1, 0, 0));

			setVec3("spotLights[" + iStr + "].ambient",      Light::spotLights[i]->ambient);
			setVec3("spotLights[" + iStr + "].diffuse",      Light::spotLights[i]->diffuse);

			setFloat("spotLights[" + iStr + "].constant",    Light::spotLights[i]->constant);
			setFloat("spotLights[" + iStr + "].linear",      Light::spotLights[i]->linear);
			setFloat("spotLights[" + iStr + "].quadratic",   Light::spotLights[i]->quadratic);

			setFloat("spotLights[" + iStr + "].cutOff",      glm::cos(glm::radians(Light::spotLights[i]->width * (1 - Light::spotLights[i]->blur))));
			setFloat("spotLights[" + iStr + "].outerCutOff", glm::cos(glm::radians(Light::spotLights[i]->width)));
		}
	}
#endif

}