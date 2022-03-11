#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>


#include "gc_3d_defs.hpp"

using namespace GC_3D;

class Geometry {
public:

    //These arrays should all have the same size.
    //They can be empty as well
    Vector<vec3> m_Pos = { {-1, -1, -1}, {1, -1, -1}, {-1, 1, -1}, {1, 1, -1},    // Front
                               {-1, -1, 1}, {1, -1, 1}, {-1, 1, 1}, {1, 1, 1},        // Back

                               {1, -1, -1}, {1, -1, 1}, {1, 1, -1}, {1, 1, 1},        // Right
                               {-1, -1, -1}, {-1, 1, -1}, {-1, -1, 1}, {-1, 1, 1},    // Left

                               {-1, -1, -1}, {1, -1, -1}, {-1, -1, 1}, {1, -1, 1},    // Bottom
                               {-1, 1, -1}, {1, 1, -1}, {-1, 1, 1}, {1, 1, 1} };      // Up

    Vector<vec3> m_Normals = { {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},
                               {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1},

                               {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
                               {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},

                               {0, -1, 0}, {0, -1, 0}, {0, -1, 0}, {0, -1, 0},
                               {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0} };
    Vector<vec2> m_TexCoord;

    Vector<uint32_t> m_Indices = { 0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7, 8, 9, 10, 9, 10, 11, 12, 13, 14, 13, 14, 15, 16, 17, 18, 17, 18, 19, 20, 21, 22, 21, 22, 23 };


    void Geometry::Bind() const
    {
        // Set each attribute pointer, if we have data for it.
        if (!m_Pos.empty())
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3), m_Pos.data());
        }
        else
        {
            glDisableClientState(GL_VERTEX_ARRAY);
        }
        if (!m_Normals.empty())
        {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, sizeof(glm::vec3), m_Normals.data());
        }
        else
        {
            glDisableClientState(GL_NORMAL_ARRAY);
        }
        if (!m_TexCoord.empty())
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, sizeof(glm::vec2), m_TexCoord.data());
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
            glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, m_Indices.data());
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, m_Pos.size());
        }
    }

};