#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#endif

#include "gc_3d_defs.hpp"
#include <SDL.h>
#include <gl/GL.h>
#include "camera.hpp"

using namespace GC_3D;

int main(int argc, char* argv[])
{
    Vector<vec3> Positions = { {0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1}, {1, 1, 0}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1} };
    int index[] = { 0, 1, 2, 1, 2, 4, 2, 4, 6, 4, 6, 7, 1, 4, 5, 4, 5, 7, 0, 1, 3, 1, 3, 5, 0, 2, 3, 2, 3, 6, 3, 5, 6, 5, 6, 7};

    /*Positions.push_back(vec3(-1, 0, 0));
    Positions.push_back(vec3(0, 1, 0));
    Positions.push_back(vec3(1, 0, 0));*/

    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    bool apprunning = true;
    while (apprunning)
    {
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {

        }
        glViewport(0, 0, 1024, 768);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glColor4f(1.0, 1.0, 1.0, 1.0);
        /*glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        
        glEnd();*/
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(vec3), Positions.data());

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, Positions.size(), GL_UNSIGNED_INT, index);

        SDL_GL_SwapWindow(win);


    }

    printf("Hello World");
    return 0;
}