// Includes
#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>


class Cube
{
public:

    void makeCube() {

        GLfloat vertices[] = {
                        1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
                       -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

                        1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
                        1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

                        1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
                       -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

                       -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
                       -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

                       -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
                        1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

                        1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
                       -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

        // normal array
        GLfloat normals1[] = {
                                0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
                                0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

                                1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
                                1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

                                0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
                                0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

                               -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
                               -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

                                0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
                                0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

                                0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
                                0, 0,-1,   0, 0,-1,   0, 0,-1 };    // v6-v5-v4

        // color array
        GLfloat colors1[] = {
                                1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
                                1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

                                1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
                                0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

                                1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
                                0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

                                1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
                                0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

                                0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
                                1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

                                0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
                                0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4


        // activate and specify pointer to vertex array
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);

        // draw a cube
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // deactivate vertex arrays after drawing
        glDisableClientState(GL_VERTEX_ARRAY);
    }

};