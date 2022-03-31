#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <string>
#include <iostream>

using namespace std;
bool loadAssImp(
	string path,
	std::vector<unsigned int>& indices,
	std::vector<glm::vec3>& vertices,
	std::vector<glm::vec2>& uvs,
	std::vector<glm::vec3>& normals
);

#endif