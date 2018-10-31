#pragma once
#include <vector>
#include <map>
#include <string>

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	static bool CheckFileExists(std::string fileName);
	static void loadModel(std::string fileName);

	static void loadImage(std::string filename);

	static std::vector<float> Vertices;
	static std::vector<unsigned int> Indices;

	static std::map<std::string, std::vector<float>> savedVerticies;
	static std::map<std::string, std::vector<unsigned int>> savedIndices;
};

