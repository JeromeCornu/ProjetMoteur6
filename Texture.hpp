#include "gc_3d_defs.hpp"

namespace GC_3D
{
    class Texture
    {

    GLuint m_Id;

    public:

        GLuint GetTexId() const { return m_Id; }

        void applyTexture(int width, int height, int bpp, char* path);
    };

}