#include "Skybox.hpp"
#include "Texture.hpp"
#include <stb_image.h>
#include <iostream>

using namespace std;
using namespace glm;
using namespace GC_3D;


unsigned int Skybox::LoadingTexture(std::filesystem::path appDir)
{
    vector<string> faces
    {
        "asset/skybox/right.png",
        "asset/skybox/left.png",
        "asset/skybox/up.png",
        "asset/skybox/down.png",
        "asset/skybox/front.png",
        "asset/skybox/back.png"
    };

    for (auto& path : faces)
    {
        path = (appDir / path).string();
    }
    unsigned int cubemapTexture = loadCubemap(faces);

    return cubemapTexture;
}

void Skybox::SkyBox_CreateTexture()
{
    textures_faces.push_back("asset/skybox/back.png");
    textures_faces.push_back("asset/skybox/front.png");
    textures_faces.push_back("asset/skybox/down.png");
    textures_faces.push_back("asset/skybox/up.png");
    textures_faces.push_back("asset/skybox/right.png");
    textures_faces.push_back("asset/skybox/left.png");

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    unsigned char* data;
    for (unsigned int i = 0; i < textures_faces.size(); i++)
    {
        data = stbi_load(textures_faces[i].c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
        );

        // Cube Map
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // mets les UV Ã  1 maximum pour pas tout casser (0 < UV < 1)
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }
}



// all the cubemap code combined in a single manageable function.
unsigned int Skybox::loadCubemap(Vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}