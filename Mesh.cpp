#include "Mesh.h"
#include "Texture.hpp"
#include "Matrix.hpp"


using namespace std;
using namespace glm;
using namespace GC_3D;



float MPosX, MPosY, MPosZ;
float MRotX, MRotY, MRotZ;
float MScaX, MScaY, MScaZ;

vec3 MvPosition = vec3(MPosX, MPosY, MPosZ);
vec3 MvRotate = vec3(MRotX, MRotY, MRotZ);
vec3 MvScale = vec3(MScaX, MScaY, MScaZ);

mat3 MTransform = mat3(MvPosition, MvRotate, MvScale);

void Mesh::InitBuffers(Vector<vec3> vertices, Vector<vec2> uvs, Vector<vec3> normals, Vector<unsigned int> indices)
{
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &Vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, Vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &Uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, Uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), uvs.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &Normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, Normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), normals.data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
}

void Mesh::initializeMesh(Vector<unsigned int> indices)
{
    
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(G_vertex_buffer_data), G_vertex_buffer_data, GL_STATIC_DRAW);


    // When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // Generate mipmaps, by the way.
    glGenerateMipmap(GL_TEXTURE_2D);

    // Textures buffers
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(G_uv_buffer_data), G_uv_buffer_data, GL_STATIC_DRAW);

    // Light buffers
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(Normals), &Normals[0], GL_STATIC_DRAW);


    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Mesh::makeMesh(GLuint iTexLoc, Texture* iTexture, Vector<unsigned int> indices) const
{
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, Uvbuffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, Vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, Normalbuffer);
    glVertexAttribPointer(
        2,                                // attribute
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, iTexture->GetTexId());
    glUniform1i(iTexLoc, 0);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

    // Draw the triangles !
    
    glDrawElements(
        GL_TRIANGLES,      // mode
        indices.size(),    // count
        GL_UNSIGNED_INT,   // type
        (void*)0           // element array buffer offset
    );
    // disable les buffers
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Mesh::SetTransform(mat3 MTransform, mat4& Model) {

    // Parametres du mesh
    mat4 Translation = translate(mat4(1.0F), vec3(MTransform[0][0], MTransform[0][1], MTransform[0][2]));
    mat4 Rotation = rotate(mat4(1.0F), 1.0f, vec3(MTransform[1][0], MTransform[1][1], MTransform[1][2]));
    mat4 Scaling = scale(mat4(1.0F), vec3(MTransform[2][0], MTransform[2][1], MTransform[2][2]));

    Model = Translation * Rotation * Scaling * mat4(1.0f);
}

void Mesh::DrawMesh(mat4 Model, Matrix matrix, GLuint ProgramID, GLuint TextureLocId, Texture TextureModel, Vector <unsigned int> indices, Camera camera, mat3 TransformModel)
{
    SetTransform(TransformModel, Model);

    // Create matrix
    matrix.ModelViewMaker(Model, camera);
    matrix.ModelViewSetter(ProgramID, TextureLocId, Model);

    // Draw the Mesh
    makeMesh(TextureLocId, &TextureModel, indices);
}

mat3 Mesh::GetTransform() {
    return MTransform;
}
