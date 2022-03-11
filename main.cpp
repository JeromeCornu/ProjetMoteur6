#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#endif

#include "GL/glew.h"
#include <SDL.h>
#include <gl/GL.h>
#include "dep/glm/glm/glm.hpp"
#include "dep/glm/glm/ext.hpp"

#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>

#include "gc_3d_defs.hpp"
#include "loadShader.cpp"
using namespace glm;

using namespace GC_3D;

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

    glewInit();

    auto prevTime = std::chrono::steady_clock::now();

    glViewport(0, 0, 1024, 768);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    static const GLfloat g_cube_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };

    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint cubebuffer;
    glGenBuffers(1, &cubebuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cubebuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertex_buffer_data), g_cube_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint programID = LoadShaders("C:/Users/bherr/Documents/projetMoteur/ProjetMoteur6/SimpleVertexShader.vertexshader", "C:/Users/bherr/Documents/projetMoteur/ProjetMoteur6/SimpleFragmentShader.fragmentshader");
    glUseProgram(programID);

    bool appRunning = true;
    while (appRunning)
    {
        SDL_Event curEvent;
        /*int width, height;
        SDL_GetWindowSize(win, &width, &height);

        float ratio = width / (float)height;

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);*/

        while (SDL_PollEvent(&curEvent))
        {
            if (curEvent.type == SDL_QUIT)
            {
                appRunning = false;
            }

            if (curEvent.window.type == SDL_WINDOWEVENT_RESIZED)
            {
                //glViewport(0.0, 0.0, width, height);
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

        // Or, for an ortho camera :
        //mat4 Projection = ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

        // Camera matrix
        mat4 View = lookAt(
            vec3(0, 0, 5), // Camera is at (4,3,3), in World Space
            vec3(0, 0, 0), // and looks at the origin
            vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

        // Model matrix : an identity matrix (model will be at the origin)
        mat4 Model = mat4(1.0f);

        mat4 Translation = translate(mat4(1.0F), vec3(0.5f, 0.5f, 0.5f));
        mat4 Rotation = rotate(mat4(1.0F), radians(0.0f), vec3(1.0F, 1.0F, 1.0F));
        mat4 Scaling = scale(mat4(1.0F), vec3(1.0F, 1.0F, 1.0F));

        Model = ((Scaling * Translation) * Rotation) * Model;

        // Our ModelViewProjection : multiplication of our 3 matrices
        mat4 mvp = Projection * View * Model;

        GLuint MatrixID = glGetUniformLocation(programID, "MVP");

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);


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

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, cubebuffer);
        glVertexAttribPointer(
            2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );


        
        // Draw the triangle !
        glBindVertexArray(vertexbuffer);
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

        glBindVertexArray(cubebuffer);
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

        /*glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);


        const float radius = 3.0;

        auto curTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> fTime = curTime - prevTime;
        float camX = sin(fTime.count()) * radius;
        float camZ = cos(fTime.count()) * radius;

        vec3 cameraPos = vec3(camX, 1.5, camZ);
        vec3 cameraTarget = vec3(0.0, 0.0, 0.0);

        // Creation de la camera
        mat4 view;
        view = lookAt(
            cameraPos,                  //Position de la camera
            cameraTarget,               //Cible Ã  regarder
            vec3(0.0, 1.0, 0.0)    //position vertical
        );

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&view[0][0]);

        mat4 projection = perspective(70.0F * (3.1416F / 180.0F), ratio, 0.01F, 100.0F);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf((float*)&projection);


        // Test de profondeur
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);


        Geometry cube;
        cube.Bind();
        cube.Draw();*/

        SDL_GL_SwapWindow(win);


    }

    //printf("Hello World");
    return 0;
}