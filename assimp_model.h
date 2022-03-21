#include "gc_3d_defs.hpp"

#ifndef OBJLOADER_H
#define OBJLOADER_H

using namespace GC_3D;

bool loadAssImp(
	const char* path,
	Vector<unsigned short>& indices,
	Vector<glm::vec3>& vertices,
	Vector<glm::vec2>& uvs,
	Vector<glm::vec3>& normals
);

#endif