#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>

namespace GC_3D
{
    class Texture
    {

    GLuint m_Id;

    public:

        GLuint GetTexId() const { return m_Id; }

        void ApplyTexture(int width, int height, int bpp, char* path);
    };

}