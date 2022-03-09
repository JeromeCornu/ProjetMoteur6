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

// Include my executables
#include "Cube.cpp"
#include "gc_3d_defs.hpp"


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

    glViewport(0, 0, 1024, 768);


    bool appRunning = true;
    while (appRunning)
    {
        SDL_Event curEvent;
        int width, height;
        SDL_GetWindowSize(win, &width, &height);

        float ratio = width / (float)height;

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        while (SDL_PollEvent(&curEvent))
        {
            if (curEvent.type == SDL_QUIT)
            {
                appRunning = false;
            }

            if (curEvent.window.type == SDL_WINDOWEVENT_RESIZED)
            {
                glViewport(0.0, 0.0, width, height);
            }
        }

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);


        // Affichage des FPS
        static unsigned int fps = 0;
        static clock_t t = clock();
        if (clock() - t > CLOCKS_PER_SEC)
        {
            char str[50] = "";
            sprintf(str, "Moteur OpenGl - FPS : %u", fps);
            SDL_SetWindowTitle(win, str);
            t = clock();
            fps = 0;
        }
        fps++;


        const float radius = 3.0;

        auto curTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> fTime = curTime - prevTime;
        float camX = glm::sin(fTime.count()) * radius;
        float camZ = glm::cos(fTime.count()) * radius;

        glm::vec3 cameraPos = glm::vec3(camX, 1.5, camZ);
        glm::vec3 cameraTarget = glm::vec3(0.0, 0.0, 0.0);

        // Creation de la camera
        glm::mat4 view;
        view = glm::lookAt(
            cameraPos,                  //Position de la camera
            cameraTarget,               //Cible � regarder
            glm::vec3(0.0, 1.0, 0.0)    //position vertical
        );

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&view[0][0]);

        glm::mat4 projection = glm::perspective(70.0F * (3.1416F / 180.0F), ratio, 0.01F, 100.0F);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf((float*)&projection);


        // Test de profondeur
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);


        // ---  DRAW HERE  ---  
        // Cube
        Cube cube;
        cube.makeCube();



        SDL_GL_SwapWindow(win);
    }

    printf("Hello World");
    return 0;
}