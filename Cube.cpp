// Includes
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


class Cube
{
public:

    void makeCube() {

        // Creation de 6 faces, chaque face carré est faite de 2 triangles, donc 6x2=12 triangles

        // Creation d'une face
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glNormal3f(0, 0, -1);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, -1.0, -1.0);
        glVertex3f(-1.0, 1.0, -1.0);
        glVertex3f(1.0, -1.0, -1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glNormal3f(0, 0, -1);
        glBegin(GL_TRIANGLES);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(1.0, 1.0, -1.0);
        glVertex3f(-1.0, 1.0, -1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glNormal3f(1, 0, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, 1.0, -1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glNormal3f(1, 0, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, 1.0, -1.0);
        glVertex3f(1.0, 1.0, 1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glNormal3f(0, 0, 1);
        glBegin(GL_TRIANGLES);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glNormal3f(0, 0, 1);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1, 1.0, 1.0, 1.0);
        glNormal3f(-1, 0, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(-1.0, -1.0, -1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1.0, 1, 1.0, 1.0);
        glNormal3f(-1, 0, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(-1.0, 1.0, -1.0);
        glVertex3f(-1.0, -1.0, -1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1.0, 1.0, 1, 1.0);
        glNormal3f(0, -1, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(-1.0, -1.0, -1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1, 1, 1.0, 1.0);
        glNormal3f(0, -1, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(1.0, -1.0, 1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1, 1.0, 1, 1.0);
        glNormal3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 1.0, -1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, -1.0);

        glEnd();

        // Creation d'une face
        glColor4f(1.0, 1, 1, 1.0);
        glNormal3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, -1.0);

        glEnd();

    }

};