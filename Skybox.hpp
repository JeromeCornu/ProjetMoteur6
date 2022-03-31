#include "gc_3d_defs.hpp"
#include <filesystem>


namespace GC_3D
{
    class Skybox {

    public:

        unsigned int textureID;

        GLuint* TexIDSkyBox;
        Vector <std::string> textures_faces;

        void SkyBox_CreateTexture();
        unsigned int loadCubemap(Vector<std::string> faces);
        unsigned int LoadingTexture(std::filesystem::path appDir);
    };


}