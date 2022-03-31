#include "gc_3d_defs.hpp"

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
        mat3 GetTransform();
    };

}