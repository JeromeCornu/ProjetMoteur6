#include "gc_3d_defs.hpp"
#include <filesystem>

namespace GC_3D
{
    class ImguiTool;

    namespace Init
    {
        SDL_Window* CreateTheWindow(ImguiTool& Imgui);
        void Vertex();
        GLuint LinkShader(std::filesystem::path Vertex, std::filesystem::path Fragment);
    };

}