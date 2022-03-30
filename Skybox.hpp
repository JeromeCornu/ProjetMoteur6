#include "gc_3d_defs.hpp"


namespace GC_3D
{
    class Skybox {

        GLuint* TexIDSkyBox;


    public:
        void SkyBox_CreateTexture();
        unsigned int loadCubemap(Vector<std::string> faces);
    };


}