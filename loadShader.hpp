#include "gc_3d_defs.hpp"

namespace GC_3D
{
    class loadShader
    {
    public:
        static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
    };

}