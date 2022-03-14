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

#define STB_IMAGE_IMPLEMENTATION
#include "dep/stb/stb_image.h"

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

    static const GLfloat g_uv_buffer_data[] = {
        0.000059f, 1.0f - 0.000004f,
        0.000103f, 1.0f - 0.336048f,
        0.335973f, 1.0f - 0.335903f,
        1.000023f, 1.0f - 0.000013f,
        0.667979f, 1.0f - 0.335851f,
        0.999958f, 1.0f - 0.336064f,
        0.667979f, 1.0f - 0.335851f,
        0.336024f, 1.0f - 0.671877f,
        0.667969f, 1.0f - 0.671889f,
        1.000023f, 1.0f - 0.000013f,
        0.668104f, 1.0f - 0.000013f,
        0.667979f, 1.0f - 0.335851f,
        0.000059f, 1.0f - 0.000004f,
        0.335973f, 1.0f - 0.335903f,
        0.336098f, 1.0f - 0.000071f,
        0.667979f, 1.0f - 0.335851f,
        0.335973f, 1.0f - 0.335903f,
        0.336024f, 1.0f - 0.671877f,
        1.000004f, 1.0f - 0.671847f,
        0.999958f, 1.0f - 0.336064f,
        0.667979f, 1.0f - 0.335851f,
        0.668104f, 1.0f - 0.000013f,
        0.335973f, 1.0f - 0.335903f,
        0.667979f, 1.0f - 0.335851f,
        0.335973f, 1.0f - 0.335903f,
        0.668104f, 1.0f - 0.000013f,
        0.336098f, 1.0f - 0.000071f,
        0.000103f, 1.0f - 0.336048f,
        0.000004f, 1.0f - 0.671870f,
        0.336024f, 1.0f - 0.671877f,
        0.000103f, 1.0f - 0.336048f,
        0.336024f, 1.0f - 0.671877f,
        0.335973f, 1.0f - 0.335903f,
        0.667969f, 1.0f - 0.671889f,
        1.000004f, 1.0f - 0.671847f,
        0.667979f, 1.0f - 0.335851f
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

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;

    GLuint programID = LoadShaders("C:/Users/bherr/Documents/GitHub/ProjetMoteur6/SimpleVertexShader.vertexshader", "C:/Users/bherr/Documents/GitHub/ProjetMoteur6/SimpleFragmentShader.fragmentshader");
    glUseProgram(programID);
    
    GLint UniformCount;

    glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &UniformCount);

    for (size_t i = 0; i < UniformCount; i++)
    {
        char uniform_name[255];
        GLsizei uniform_name_length;
        GLint size;
        GLenum type;
        glGetActiveUniform(programID, i, 255, &uniform_name_length, &size, &type, uniform_name);
        std::cout << "c le debug : " << std::string(uniform_name, uniform_name_length) << " [" << i << "]" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    int width = 902;
    int height = 634;
    int bpp = 1;

    stbi_uc* Image = stbi_load("C:/Users/bherr/Pictures/goblin.png", &width, &height, &bpp, 3);

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


    bool appRunning = true;
    while (appRunning)
    {

        static GLfloat g_color_buffer_data[12 * 3 * 3];
        for (int v = 0; v < 12 * 3; v++) {
            g_color_buffer_data[3 * v + 0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            g_color_buffer_data[3 * v + 1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            g_color_buffer_data[3 * v + 2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }

        glGenBuffers(1, &colorbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

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
            vec3(4, 3, 5), // Camera is at (4,3,3), in World Space
            vec3(0, 0, 0), // and looks at the origin
            vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

        // Model matrix : an identity matrix (model will be at the origin)
        mat4 Model = mat4(1.0f);

        mat4 Translation = translate(mat4(1.0F), vec3(0.0f, 0.0f, 1.0f));
        mat4 Rotation = rotate(mat4(1.0F), radians(45.0f), vec3(1.0F, 1.0F, 1.0F));
        mat4 Scaling = scale(mat4(1.0F), vec3(2.0F, 2.0F, 2.0F));

        Model = ((Scaling * Translation) * Rotation) * Model;

        mat4 Model2 = mat4(1.0f);

        mat4 Translation2 = translate(mat4(1.0F), vec3(0.0f, 0.0f, 0.0f));
        mat4 Rotation2 = rotate(mat4(1.0F), radians(0.0f), vec3(1.0F, 1.0F, 1.0F));
        mat4 Scaling2 = scale(mat4(1.0F), vec3(1.0F, 1.0F, 1.0F));

        Model2 = ((Scaling2 * Translation2) * Rotation2) * Model2;

        // Our ModelViewProjection : multiplication of our 3 matrices
        mat4 mvp = Projection * View * Model;

        mat4 mvp2 = Projection * View * Model2;

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

        //glUniform1i(0, Texture);

        //glUniform2f(2, -0.001f, 0.011f);
       // glUniform2f(3, 1.0f, 1.0f);

        // Draw the triangle !
        //glBindVertexArray(vertexbuffer);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp2[0][0]);

        //glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, cubebuffer);
        glVertexAttribPointer(
            0,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        ); // Starting from vertex 0; 3 vertices total -> 1 triangle

        //glBindVertexArray(cubebuffer);
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