#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>

namespace shader
{
    class loadShader
    {
    public:
        static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
    };

}