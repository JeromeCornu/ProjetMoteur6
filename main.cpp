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

int main(int argc, char* argv[])
{
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

    auto prevTime = std::chrono::steady_clock::now();

    bool appRunning = true;
    while (appRunning)
    {
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {
            if (curEvent.type == SDL_QUIT)
            {
                appRunning = false;
            }
        }

        glViewport(0, 0, 1024, 768);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);


        const float radius = 0.5;

        auto curTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> fTime = curTime - prevTime;
        float camX = glm::sin(fTime.count()) * radius;
        float camZ = glm::cos(fTime.count()) * radius;

        glm::vec3 cameraPos = glm::vec3(camX, 1.0, camZ);
        glm::vec3 cameraTarget = glm::vec3(0.0, 0.0, 0.0);

        // Creation de la camera
        glm::mat4 view;
        view = glm::lookAt(
            cameraPos,                  //Position de la camera
            cameraTarget,               //Cible à regarder
            glm::vec3(0.0, 1.0, 0.0)    //position vertical
        );

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&view[0][0]);



        // Test de profondeur
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);


        // Creation d'un triangle
        glColor4f(0.0, 1.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);

        // Creation d'un autre triangle
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES);
        glVertex3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);


        glEnd();

        SDL_GL_SwapWindow(win);

    }

    printf("Hello World");
    return 0;
}