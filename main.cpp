#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include "dep/glm/glm/glm.hpp"
#include "dep/glm/glm/ext.hpp"

#include "gc_3d_defs.hpp"
#include "loadShader.hpp"
#include "CubeTuto.hpp"


using namespace GC_3D;
using namespace shader;
using namespace cube;

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
    glewInit();



    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    // Create and compile our GLSL program from the shaders
    GLuint programID = shader::loadShader::LoadShaders("C:/Users/jcornu/Documents/GitHub/ProjetMoteur6/SimpleVertexShader.txt", "C:/Users/jcornu/Documents/GitHub/ProjetMoteur6/SimpleFragmentShader.txt");

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Boucle principale
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
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        // Use our shader
        glUseProgram(programID);

        /*
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);*/


        // create cube
        cube::CubeTuto cube;
        cube.makeCube();



        SDL_GL_SwapWindow(win);
    }

    printf("Hello World");
    return 0;
}