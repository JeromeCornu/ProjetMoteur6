#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>

namespace GC_3D
{
    class Texture;

    class CubeTuto
    {

        Texture* m_Texture;

    public:
        void makeCube (GLuint iTexLoc, Texture* iTex);
        void initializeCube();
    };

}