#pragma once
#include "gc_3d_defs.hpp"

using namespace std;
namespace GC_3D
{
    class Texture
    {
    public:

        GLuint m_Id;

        GLuint GetTexId() const { return m_Id; }

        void applyTexture(int width, int height, int bpp, string path);
        GLuint applySkybox(int width, int height, int bpp, char* path);
    };

};