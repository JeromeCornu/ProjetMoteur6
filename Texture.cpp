#include "Texture.hpp"
#include "stb_image.h"


using namespace GC_3D;

void Texture::applyTexture(int width, int height, int bpp, char* path)
{
	stbi_uc* Image = stbi_load(path, &width, &height, &bpp, 3);

	glGenTextures(1, &m_Id);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, m_Id);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(Image);
}

GLuint Texture::applySkybox(int width, int height, int bpp, char* path)
{
	stbi_uc* Image = stbi_load(path, &width, &height, &bpp, 3);

	glGenTextures(1, &m_Id);

	return m_Id;
}