#pragma once
#include "gc_3d_defs.hpp"
#include "camera.hpp"
#include "Texture.hpp"
#include "Matrix.hpp"

using namespace std;
using namespace glm;
using namespace GC_3D;

namespace GC_3D
{
    class Texture;


    class Mesh
    {
        GLuint Uvbuffer;
        GLuint Vertexbuffer;
        GLuint Normalbuffer;
        GLuint elementbuffer;
        Texture* m_Texture;


        GLfloat* G_vertex_buffer_data;
        GLfloat* G_uv_buffer_data;
        GLfloat* Normals;



    public:
        void InitBuffers(Vector<vec3> vertices, Vector<vec2> uvs, Vector<vec3> normals, Vector<unsigned int> indices);
        void initializeMesh(Vector<unsigned int> indices);
        void makeMesh(GLuint iTexLoc, Texture* iTex, Vector<unsigned int> indices) const;
        void SetTransform(mat3 Transform, mat4& Model);
        void DrawMesh(mat4 Model, Matrix matrix, GLuint ProgramID, GLuint TextureLocId, Texture TextureModel, Vector <unsigned int> indices, Camera camera, mat3 TransformModel);
        mat3 GetTransform();
    };

}