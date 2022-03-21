#include "gc_3d_defs.hpp"
#include <iostream>

using namespace GC_3D;
using namespace std;

void Geometry::Bind() const
{
    // Set each attribute pointer, if we have data for it.
    if (!m_Pos.empty())
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(vec3), m_Pos.data());
    }
    else
    {
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    if (!m_Normals.empty())
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, sizeof(vec3), m_Normals.data());
    }
    else
    {
        glDisableClientState(GL_NORMAL_ARRAY);
    }
    if (!m_TexCoord.empty())
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, sizeof(vec2), m_TexCoord.data());
    }
    else
    {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}

void Geometry::Draw() const
{
    if (!m_Indices.empty())
    {
        static const GLuint Size = 422;
        Vector<GLfloat> m_PosTest;
        static GLfloat g_vertex_buffer_data[Size] = {};

        for (size_t i = 0; i < m_Pos.size(); i+=3)
        {
            m_PosTest.push_back(m_Pos[i][0]);
            m_PosTest.push_back(m_Pos[i][1]);
            m_PosTest.push_back(m_Pos[i][2]);
        }

        for (size_t i = 0; i < m_Pos.size(); i++)
        {
            for (size_t j = 0; j < m_Pos.size(); j++)
            {
                g_vertex_buffer_data[j] = m_PosTest[i];
            }
        }
        GLuint Buffer;
        glGenBuffers(1, &Buffer);
        glBindBuffer(GL_ARRAY_BUFFER, Buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, Buffer);
        glVertexAttribPointer(
            0,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );
        glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, m_Indices.data());
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, m_Pos.size());
    }
}

Geometry Geometry::MakeSphere(float iRadius)
{
    unsigned int subDivHemi = 30;
    unsigned int subDivHeight = subDivHemi / 2;

    float stepPhi = 2 * pi<float>() / subDivHemi;
    float stepTheta = pi<float>() / subDivHeight;

    uint32_t const numVtx = (subDivHemi * (subDivHeight - 1) + 2);

    Geometry geom;
    geom.m_Pos.resize(numVtx);
    geom.m_Normals.resize(numVtx);
    //geom.m_TexCoord.resize(24);

    vec3* posPtr = geom.m_Pos.data();
    vec3* normalPtr = geom.m_Normals.data();
    *posPtr = vec3(0.0, iRadius, 0.0);
    *normalPtr = vec3(0.0, 1.0, 0.0);
    ++posPtr;
    ++normalPtr;
    for (unsigned int j = 0; j < subDivHemi - 1; ++j)
    {
        geom.m_Indices.push_back(0);
        geom.m_Indices.push_back(1 + j);
        geom.m_Indices.push_back(2 + j);
    }
    geom.m_Indices.push_back(0);
    geom.m_Indices.push_back(1 + subDivHemi - 1);
    geom.m_Indices.push_back(1);

    for (unsigned int i = 1; i < subDivHeight; ++i)
    {
        float theta = stepTheta * (float(subDivHeight) / 2.0 - i);
        float cosTheta = cos(theta);
        float sinTheta = sin(theta);
        for (unsigned int j = 0; j < subDivHemi; ++j)
        {
            if (i != subDivHeight - 1)
            {
                if (j != subDivHemi - 1)
                {
                    geom.m_Indices.push_back(1 + (i - 1) * subDivHemi + j);
                    geom.m_Indices.push_back(1 + i * subDivHemi + j);
                    geom.m_Indices.push_back(2 + i * subDivHemi + j);
                    geom.m_Indices.push_back(1 + (i - 1) * subDivHemi + j);
                    geom.m_Indices.push_back(2 + i * subDivHemi + j);
                    geom.m_Indices.push_back(2 + (i - 1) * subDivHemi + j);
                }
                else
                {
                    geom.m_Indices.push_back(1 + (i - 1) * subDivHemi + j);
                    geom.m_Indices.push_back(1 + i * subDivHemi + j);
                    geom.m_Indices.push_back(1 + i * subDivHemi);
                    geom.m_Indices.push_back(1 + (i - 1) * subDivHemi + j);
                    geom.m_Indices.push_back(1 + i * subDivHemi);
                    geom.m_Indices.push_back(1 + (i - 1) * subDivHemi);
                }
            }

            float phi = j * stepPhi;
            float cosPhi = cos(phi);
            float sinPhi = sin(phi);
            *normalPtr = vec3(cosPhi, 0, sinPhi) * cosTheta + vec3(0, sinTheta, 0);
            *normalPtr = normalize(*normalPtr);
            *posPtr = iRadius * *normalPtr;
            ++posPtr;
            ++normalPtr;
        }
    }

    *posPtr = vec3(0.0, -iRadius, 0.0);
    *normalPtr = vec3(0.0, -1.0, 0.0);
    ++posPtr;
    ++normalPtr;
    for (unsigned int j = 0; j < subDivHemi - 1; ++j)
    {
        geom.m_Indices.push_back(1 + (subDivHeight - 2) * subDivHemi + j);
        geom.m_Indices.push_back(2 + (subDivHeight - 2) * subDivHemi + j);
        geom.m_Indices.push_back(numVtx - 1);
    }
    geom.m_Indices.push_back(1 + (subDivHeight - 2) * subDivHemi + subDivHemi - 1);
    geom.m_Indices.push_back(1 + (subDivHeight - 2) * subDivHemi);
    geom.m_Indices.push_back(numVtx - 1);

    return geom;
}