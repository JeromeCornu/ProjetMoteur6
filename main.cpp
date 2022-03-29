#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "gc_3d_defs.hpp"

#include "Init.hpp"
#include "CubeTuto.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "FPS.hpp"
#include "Matrix.hpp"

#include <iostream>
#include <filesystem>
#include "PathFinder.hpp"
#include "objLoader.hpp"
#include "Mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "dep/stb/stb_image.h"

#include "gc_3d_defs.hpp"
#include "loadShader.cpp"
#include "FPSCounter.hpp"
#include "Camera.hpp"

using namespace glm;
using namespace std;
using namespace chrono;
using namespace GC_3D;


int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    int ScreenWidth = 1024;
    int ScreenHeight = 768;

    Camera Camera;
    //Camera.direction = -Camera.position;

    FPSCounter Counter;

    SDL_Window* Win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        ScreenWidth,
        ScreenHeight,
        windowsFlags);

    SDL_GLContext context = SDL_GL_CreateContext(Win);
    SDL_GL_MakeCurrent(Win, context);

    glewInit();

    auto prevTime = std::chrono::steady_clock::now();

    glViewport(0, 0, ScreenWidth, ScreenHeight);


    Geometry Sphere;
    Sphere.MakeSphere(5);
    Sphere.Bind();


    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_uv_buffer_data[] = {
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

        0.0f, 1.0f,// face derrière
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

    static const GLfloat g_cube_vertex_buffer_data[] = {
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
         -1.0f, -1.0f, -1.0f
    };

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    GLuint CubeBuffer;
    glGenBuffers(1, &CubeBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, CubeBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertex_buffer_data), g_cube_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint programID = LoadShaders("C:/Users/bapti/source/repos/JeromeCornu/ProjetMoteur6/SimpleVertexShader.vertexshader", "C:/Users/bapti/source/repos/JeromeCornu/ProjetMoteur6/SimpleFragmentShader.fragmentshader");
    glUseProgram(programID);

    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    int width = 225;
    int height = 225;
    int bpp = 1;

    stbi_uc* Image = stbi_load("C:/Users/bapti/Pictures/hacker.jpg", &width, &height, &bpp, 3);

    GLuint Texture;

    glGenTextures(1, &Texture);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, Texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);



    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_WarpMouseInWindow(Win, ScreenWidth / 2, ScreenHeight / 2);

    bool appRunning = true;
    SDL_ShowCursor(SDL_DISABLE);

    bool ZPressed = false;

    bool SPressed = false;

    bool DPressed = false;

    bool QPressed = false;

    while (appRunning)
    {
        Counter.Increment(Win);

        SDL_Event curEvent;

        float ratio = width / (float)height;

        while (SDL_PollEvent(&curEvent))
        {
            if (curEvent.type == SDL_KEYDOWN)
            {
                switch (curEvent.key.keysym.sym)
                {
                case SDLK_z:
                    ZPressed = true;
                    break;
                case SDLK_s:
                    SPressed = true;
                    break;
                case SDLK_q:
                    QPressed = true;
                    break;
                case SDLK_d:
                    DPressed = true;
                    break;
                }
            }
            else if (curEvent.type == SDL_KEYUP)
            {
                switch (curEvent.key.keysym.sym)
                {
                case SDLK_z:
                    ZPressed = false;
                    break;
                case SDLK_s:
                    SPressed = false;
                    break;
                case SDLK_q:
                    QPressed = false;
                    break;
                case SDLK_d:
                    DPressed = false;
                    break;
                }
            }
            if (curEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                appRunning = false;
            }
        }

        Vector<GLboolean> PressedButtons = {ZPressed, SPressed, QPressed, DPressed};

        Camera.Move(PressedButtons);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        Camera.ComputeMatricesFromInputs(ScreenWidth, ScreenHeight, Win);
        mat4 ProjectionMatrix = Camera.GetProjectionMatrix();
        mat4 ViewMatrix = Camera.GetViewMatrix();

        auto curTime = steady_clock::now();
        std::chrono::duration<float> fTime = curTime - prevTime;
        float turnSin = sin(fTime.count());
        float turnCos = cos(fTime.count());

        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 5; j++)
            {
                for (size_t k = 0; k < 5; k++)
                {
                    for (size_t l = 0; l < 5; l++)
                    {

                        mat4 Translation = translate(mat4(1.0), vec3(j * 2 + turnSin * 5, k * 2 + i * 20 + turnSin * 10, l * 2 + turnCos * 20));
                        mat4 Rotation = rotate(mat4(1.0), 0.0f, vec3(1.0f, 1.0f, 1.0f));

                        mat4 ModelMatrix = mat4(1.0);
                        ModelMatrix = Rotation * Translation * ModelMatrix;
                        mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;



                        GLuint MatrixID = glGetUniformLocation(programID, "MVP");

                        // Send our transformation to the currently bound shader, in the "MVP" uniform
                        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
                        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
                        glEnableVertexAttribArray(0);
                        glBindBuffer(GL_ARRAY_BUFFER, CubeBuffer);
                        glVertexAttribPointer(
                            0,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                            3,                                // size
                            GL_FLOAT,                         // type
                            GL_FALSE,                         // normalized?
                            0,                                // stride
                            (void*)0                          // array buffer offset
                        );

                        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

                        //Sphere.Draw();
                    }
                }
            }
        }
    }
    return 0;
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