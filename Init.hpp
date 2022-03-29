#include "gc_3d_defs.hpp"

namespace GC_3D
{

    class Init
    {

    public:
        SDL_Window* CreateTheWindow();
        void Vertex();
        GLuint LinkShader();
    };

}