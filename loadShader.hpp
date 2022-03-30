#include "gc_3d_defs.hpp"
#include <filesystem>

namespace GC_3D
{
    class loadShader
    {
    public:
        static GLuint LoadShaders(std::filesystem::path vertex_file_path, std::filesystem::path fragment_file_path);
    };

}