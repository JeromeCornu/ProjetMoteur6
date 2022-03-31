#include "gc_3d_defs.hpp"

namespace GC_3D
{
    class Camera;

    class Matrix
    {

    public:
        mat4 ModelViewMaker(mat4 Model, Camera MainCamera);

        void ModelViewSetter(GLuint Program, mat4 Model);
    };

}