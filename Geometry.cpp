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

class Geometry {
public:

    //These arrays should all have the same size.
    //They can be empty as well
    GC_3D::Vector<glm::vec3> m_Pos =
    {
        {   -1,     1,      1  },       // top face
        {   -1,     1,     -1  },
        {    1,     1,     -1  },
        {    1,     1,      1  },

        {    1,    -1,      1  },       // bottom face
        {    1,    -1,     -1  },
        {   -1,    -1,     -1  },
        {   -1,    -1,      1  },

        {   -1,     1,      1  },       // front face
        {    1,     1,      1  },
        {    1,    -1,      1  },
        {   -1,    -1,      1  },

        {   -1,     1,     -1  },       // behind face
        {    1,     1,     -1  },
        {    1,    -1,     -1  },
        {   -1,    -1,     -1  },

        {   -1,     1,      1  },       // left face
        {   -1,    -1,     -1  },
        {   -1,    -1,      1  },
        {   -1,     1,     -1  },

        {    1,     1,     -1  },       // right face
        {    1,     1,      1  },
        {    1,    -1,      1  },
        {    1,    -1,     -1  }
    };

    GC_3D::Vector<glm::vec3> m_Normals =
    {
        {   0,     1,     0  },       // top face
        {   0,     1,     0  },
        {   0,     1,     0  },
        {   0,     1,     0  },

        {   0,    -1,     0  },       // bottom face
        {   0,    -1,     0  },
        {   0,    -1,     0  },
        {   0,    -1,     0  },

        {   0,    0,      1  },       // front face
        {   0,    0,      1  },
        {   0,    0,      1  },
        {   0,    0,      1  },

        {   0,    0,     -1  },       // behind face
        {   0,    0,     -1  },
        {   0,    0,     -1  },
        {   0,    0,     -1  },

        {   -1,    0,     0  },       // left face
        {   -1,    0,     0  },
        {   -1,    0,     0  },
        {   -1,    0,     0  },

        {    1,    0,     0  },       // right face
        {    1,    0,     0  },
        {    1,    0,     0  },
        {    1,    0,     0  }
    };

    GC_3D::Vector<glm::vec2> m_TexCoord;

    GC_3D::Vector<uint32_t> m_Indices =
    {
        // First Cube
        1, 0, 7,    // left face
        1, 6, 7,
        1, 2, 3,    // top face
        1, 0, 3,
        2, 3, 4,    // right face
        2, 5, 4,
        6, 7, 4,    // bot face
        6, 5, 4,
        0, 7, 4,    // front face
        0, 3, 4,
        1, 6, 5,    // behind face
        1, 2, 5,
        
        // Second Cube
        9, 8, 15,    // left face
        9, 14, 15,
        9, 10, 11,    // top face
        9, 8, 11,
        10, 11, 12,   // right face
        10, 13, 12,
        14, 15, 12,  // bot face
        14, 13, 12,
        8, 15, 12,   // front face
        8, 11, 12,
        9, 14, 13,   // behind face
        9, 10, 13,
        
        // Third Cube
        16, 15, 22,  // left face
        16, 21, 22,
        16, 17, 18,  // top face
        16, 15, 18,
        17, 18, 19,  // right face
        17, 20, 19,
        21, 22, 19,  // bot face
        21, 20, 19,
        15, 22, 19,  // front face
        15, 18, 19,
        16, 21, 20,  // behind face
        16, 17, 20
    };

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