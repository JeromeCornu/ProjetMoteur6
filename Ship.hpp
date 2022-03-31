#pragma once
#include "gc_3d_defs.hpp"
#include <string>
#include <iostream>
#include "objLoader.hpp"
#include "Mesh.h"

using namespace std;
namespace GC_3D
{
    class Vessel
    {
        string TexturePath;
        Texture ShipTexture;
        string ModelPath;
        Mesh ShipMesh;

        Vector<vec3> vertices;
        Vector<vec2> uvs;
        Vector<vec3> normals;
        Vector<unsigned int> indices;

    public:
        void InitShip(string Name, string Color);
        void DrawShip(mat4 Model, Matrix matrix, GLuint ProgramID, GLuint TextureLocId, Camera Camera);
    };

};