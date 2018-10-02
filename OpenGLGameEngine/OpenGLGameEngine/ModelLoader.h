#pragma once
#include <vector>
#include <string>

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	static void loadModel(std::string fileName	);

	static std::vector<float> Vertices;
	static std::vector<unsigned int> Indices;
};

