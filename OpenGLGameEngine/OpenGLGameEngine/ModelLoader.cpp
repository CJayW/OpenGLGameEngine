#include "ModelLoader.h"

#include <iostream>
#include <fstream>

#include "LevelFileManager.h"
#include "EditorDebug.h"

#include <algorithm>


ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

std::vector<float> ModelLoader::Vertices;
std::vector<unsigned int> ModelLoader::Indices;

std::map<std::string, std::vector<float>> ModelLoader::savedVerticies;
std::map<std::string, std::vector<unsigned int>> ModelLoader::savedIndices;

bool ModelLoader::CheckFileExists(std::string fileName)
{

	std::ifstream ip(fileName);
	if (!ip.good()) {
		return false;
	}
	return true;
}


void ModelLoader::loadModel(std::string fileName)
{
	std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
	
	if (savedVerticies.find(fileName) != savedVerticies.end()) {
		Vertices = savedVerticies[fileName];
		Indices = savedIndices[fileName];

		return;
	}

	bool afterHeader = false;
	int totalVertexes = -1;
	int totalFaces = -1;

	std::string line;
	std::ifstream ip(fileName);

	while (ip.good()) {
		std::getline(ip, line);
		if (!afterHeader) {
			if (totalVertexes == -1 || totalFaces == -1) {
				std::vector<std::string> words = LevelFileManager::splitBy(line, ' ');
				if (words.size() > 2 && words[0] == "element") {
					if (words[1] == "vertex") {
						totalVertexes = std::stoi(words[2]);

						continue;
					} else if (words[1] == "face") {
						totalFaces = std::stoi(words[2]);
						continue;
					}
				}
			}
			if (line == "end_header") {
				afterHeader = true;
			}
		}
		if(afterHeader){
			for (int i = 0; i < totalVertexes; i++) {
				std::getline(ip, line);
				std::vector<std::string> splitLine = LevelFileManager::splitBy(line, ' ');
				//pos
				savedVerticies[fileName].push_back(std::stof(splitLine[1]));
				savedVerticies[fileName].push_back(std::stof(splitLine[2]));
				savedVerticies[fileName].push_back(std::stof(splitLine[0]));
				//rbg
				savedVerticies[fileName].push_back(std::stof(splitLine[6]) / 255);
				savedVerticies[fileName].push_back(std::stof(splitLine[7]) / 255);
				savedVerticies[fileName].push_back(std::stof(splitLine[8]) / 255);

				//normals
				savedVerticies[fileName].push_back(std::stof(splitLine[4]));
				savedVerticies[fileName].push_back(std::stof(splitLine[5]));
				savedVerticies[fileName].push_back(std::stof(splitLine[3]));
			}
			for (int i = 0; i < totalFaces; i++) {
				std::getline(ip, line);
				std::vector<std::string> splitLine = LevelFileManager::splitBy(line, ' ');
				
				savedIndices[fileName].push_back(std::stoi(splitLine[1]));
				savedIndices[fileName].push_back(std::stoi(splitLine[2]));
				savedIndices[fileName].push_back(std::stoi(splitLine[3]));
			}
			break;
		}
	}
	ip.close();

	Vertices = savedVerticies[fileName];
	Indices = savedIndices[fileName];

}