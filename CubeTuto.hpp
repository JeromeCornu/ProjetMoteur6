#include "gc_3d_defs.hpp"

using namespace std;
using namespace glm;
using namespace GC_3D;

namespace GC_3D
{
    class Texture;

    class CubeTuto
    {

        Texture* m_Texture;

    public:
        void initializeCube() const;
        void makeCube(GLuint iTexLoc, Texture* iTex) const;
        void SetTransform(mat3 Transform, mat4& Model);
        mat3 GetTransform();
    };

}