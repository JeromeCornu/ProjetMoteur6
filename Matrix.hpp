#include "gc_3d_defs.hpp"

namespace GC_3D
{
    class Texture;

    class Matrix
    {

    public:
        mat4 ModelViewMaker(mat4 Model);
        void ModelViewSetter(GLuint Program, GLuint &TextureLocId, mat4 Model);
    };

}