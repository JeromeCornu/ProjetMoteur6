#include "gc_3d_defs.hpp"

namespace GC_3D
{
    class ImguiTool;

    namespace Init
    {
        SDL_Window* CreateTheWindow(ImguiTool& Imgui);
        void Vertex();
        GLuint LinkShader();
    };

}