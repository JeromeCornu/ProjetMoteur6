#define STB_IMAGE_IMPLEMENTATION
#include "Ship.hpp"

using namespace GC_3D;

void Vessel::InitShip(string Name, string Color)
{
	TexturePath = "asset/Ultimate Spaceships - May 2021/" + Name + "/Textures/" + Name + "_" + Color + ".png";
	ModelPath = "asset/Ultimate Spaceships - May 2021/" + Name + "/OBJ/" + Name + ".obj";
	ShipTexture.applyTexture(2048, 2048, 1, TexturePath);
	loadAssImp(ModelPath, indices, vertices, uvs, normals);
	ShipMesh.InitBuffers(vertices, uvs, normals, indices);
}

void Vessel::DrawShip(mat4 Model, Matrix matrix, GLuint ProgramID, GLuint TextureLocId, Camera Camera)
{
	ShipMesh.DrawMesh(Model, matrix, ProgramID, TextureLocId, ShipTexture, indices, Camera);
}