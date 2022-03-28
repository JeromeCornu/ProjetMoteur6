#include "CubeTuto.hpp"
#include "Texture.hpp"

using namespace std;
using namespace glm;
using namespace GC_3D;

GLuint Uvbuffer;
GLuint Vertexbuffer;
GLuint Normalbuffer;

// Position
static const GLfloat G_vertex_buffer_data[] = {
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, // face avant

        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, // face gauche

        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, // face derri�re

        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, // face droite

         -1.0f, 1.0f, 1.0f,
         -1.0f, 1.0f, -1.0f,
         1.0f, 1.0f, -1.0f,
         1.0f, 1.0f, -1.0f,
         1.0f, 1.0f, 1.0f,
         -1.0f, 1.0f, 1.0f, // face dessus

         -1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f, -1.0f // face dessous
};

// Color
/*
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};
*/

// UV
static const GLfloat G_uv_buffer_data[] = {
        0.0f, 1.0f,// face avant
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,// face gauche
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,// face derri�re
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,// face droite
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,// face dessus
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,// face dessous
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
};

// normal array
GLfloat Normals[] = {
                        0, 0, 1,   0, 0, 1,   0, 0, 1,      // face avant
                        0, 0, 1,   0, 0, 1,   0, 0, 1,

                        -1, 0, 0,   -1, 0, 0,   -1, 0, 0,   // face gauche
                        -1, 0, 0,   -1, 0, 0,   -1, 0, 0,

                        0, 0, -1,   0, 0, -1,   0, 0, -1,   // face derriere
                        0, 0, -1,   0, 0, -1,   0, 0, -1,

                        1, 0, 0,  1, 0, 0,  1, 0, 0,        // face droite
                        1, 0, 0,  1, 0, 0,  1, 0, 0,

                        0, 1, 0,   0, 1, 0,   0, 1, 0,      // face dessus
                        0, 1, 0,   0, 1, 0,   0, 1, 0,

                        0, -1, 0,   0, -1, 0,   0, -1, 0,      // face dessous
                        0, -1, 0,   0, -1, 0,   0, -1, 0
};


float PosX, PosY, PosZ;
float RotX, RotY, RotZ;
float ScaX, ScaY, ScaZ;

vec3 vPosition = vec3(PosX, PosY, PosZ);
vec3 vRotate = vec3(RotX, RotY, RotZ);
vec3 vScale = vec3(ScaX, ScaY, ScaZ);

mat3 Transform = mat3(vPosition, vRotate, vScale);


void CubeTuto::initializeCube() const
{
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &Vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, Vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(G_vertex_buffer_data), G_vertex_buffer_data, GL_STATIC_DRAW);


    // When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // Generate mipmaps, by the way.
    glGenerateMipmap(GL_TEXTURE_2D);

    // Textures buffers
    glGenBuffers(1, &Uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, Uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(G_uv_buffer_data), G_uv_buffer_data, GL_STATIC_DRAW);

    // Light buffers
    glGenBuffers(1, &Normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, Normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Normals), &Normals[0], GL_STATIC_DRAW);

}

void CubeTuto::makeCube(GLuint iTexLoc, Texture* iTexture) const
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

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares

    // disable les buffers
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void CubeTuto::SetTransform(mat3 Transform, mat4 &Model) {

    // Parametres des cubes
    mat4 Translation = translate(mat4(1.0F), vec3(Transform[0][0], Transform[0][1], Transform[0][2]));
    mat4 Rotation = rotate(mat4(1.0F), 1.0f, vec3(Transform[1][0], Transform[1][1], Transform[1][2]));
    mat4 Scaling = scale(mat4(1.0F), vec3(Transform[2][0], Transform[2][1], Transform[2][2]));

    Model = Translation * Rotation * Scaling * mat4(1.0f);
}

mat3 CubeTuto::GetTransform() {
    return Transform;
}

/* FRUSTUM CULLING
* Utiliser les snippets "Math" et la suite du gc_3d_defs du prof (sur le drive)
produit scalaire = position * normal face cube =
regarder si c'est positif ou negatif
(on voit si c'est derriere ou devant leS faces des "cube") donc on l'affiche ou pas

    on va pas tester tt les points : donner un centre et prendre la sphere englobante
    si elle est dehors le frustum completement, alors le modele de la sphere est dehors 
    Si c'est plus de - du rayon de la sphere, pb pcq elle est encore dedans
    Si c'est moins c'est nickel


Pour trouver normal = regle de la main droite

*/