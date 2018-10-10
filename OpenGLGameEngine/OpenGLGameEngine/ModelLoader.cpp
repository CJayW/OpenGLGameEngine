#include "ModelLoader.h"

#include "LevelFileManager.h"

#include <iostream>
#include <fstream>

ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

std::vector<float> ModelLoader::Vertices;

std::vector<unsigned int> ModelLoader::Indices;

void ModelLoader::loadModel(std::string fileName)
{
	Vertices.clear();
	Indices.clear();

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
				Vertices.push_back(std::stof(splitLine[1]));
				Vertices.push_back(std::stof(splitLine[2]));
				Vertices.push_back(std::stof(splitLine[0]));
				//rbg
				Vertices.push_back(std::stof(splitLine[6]) / 255);
				Vertices.push_back(std::stof(splitLine[7]) / 255);
				Vertices.push_back(std::stof(splitLine[8]) / 255);

				//Vertices.push_back(1);
				//Vertices.push_back(1);
				//Vertices.push_back(1);
				//normals
				Vertices.push_back(std::stof(splitLine[3]));
				Vertices.push_back(std::stof(splitLine[4]));
				Vertices.push_back(std::stof(splitLine[5]));
			}
			for (int i = 0; i < totalFaces; i++) {
				std::getline(ip, line);
				std::vector<std::string> splitLine = LevelFileManager::splitBy(line, ' ');
				
				Indices.push_back(std::stoi(splitLine[1]));
				Indices.push_back(std::stoi(splitLine[2]));
				Indices.push_back(std::stoi(splitLine[3]));
			}
			break;
		}
	}
	ip.close();
}

