#include "gc_3d_defs.hpp"

namespace GC_3D
{
    class Texture;

    class CubeTuto
    {

        Texture* m_Texture;

    public:
        void initializeCube() const;
        void makeCube(GLuint iTexLoc, Texture* iTex) const;
        mat4 SetTransform(mat3 Transform);
        mat3 GetTransform();
    };

}