#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "gc_3d_defs.hpp"

#include "loadShader.hpp"
#include "CubeTuto.hpp"
#include "Texture.hpp"
#include <iostream>

using namespace std;
using namespace glm;
using namespace GC_3D;


int main(int argc, char* argv[])
{
    CubeTuto cube;
    Texture texture;

    /* ------------------------------------------------- INITIALIZATION PROJECT ------------------------------------------------------------- */

    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


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

    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint programID = GC_3D::loadShader::LoadShaders("C:\\Users\\jcornu\\Documents\\GitHub\\ProjetMoteur6\\SimpleVertexShader.txt", "C:\\Users\\jcornu\\Documents\\GitHub\\ProjetMoteur6\\SimpleFragmentShader.txt");
    glUseProgram(programID);


    /* --------------------------------------------- INITIALIZATION CREATIONS --------------------------------------------------------- */

    // initialize cube
    cube.initializeCube();
    // initialize texture
    texture.applyTexture(500, 500, 1, "C:\\Users\\jcornu\\Pictures\\uwu.jpg");

    /* --------------------------------------------- INITIALIZATION TABLEAU --------------------------------------------------------- */

    vector<CubeTuto> cubesArray;

    /* --------------------------------------------------- START LOOP ----------------------------------------------------------- */

    auto startTime = Clock::now();

    // Nb cube wished
    //int i = 0;
    // Nb cube drawn
    int count = 0;

    cout << "Saisir le nombre de cube voulu : ";
    cin >> count;
    cout << "On affiche " << count << " cube(s)." << endl;


    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    bool appRunning = true;
    while (appRunning)
    {
        // Position of each cube - initialization
        float positionX = 0;
        float positionY = 0;
        float positionZ = 0;

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
        // Clear the screen
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

        /* ---------------------------------------------------- FPS ------------------------------------------------------------- */

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

        /* ------------------------------------------------- MATRICES ------------------------------------------------------------- */

        mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

        // Or, for an ortho camera :
        //mat4 Projection = ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

        //auto curTime = Clock::now();

        // Camera matrix
        mat4 View = lookAt(
            //vec3(0, 0, 3.0*glm::cos(Seconds(curTime - startTime))), // Camera is at (4,3,3), in World Space
            vec3(4, 3, 3),
            vec3(0, 0, -5), // and looks at the origin
            vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );


        // Position of the cube
        GLuint MatrixID;
        GLuint TextureLocId;

        for (int i = 0; i < count; i++)
        {
            auto curTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> fTime = curTime - prevTime;
            float turn = sin(fTime.count());

            mat4 Translation = translate(mat4(1.0F), vec3(0.0f + positionX, 0.0f + positionY, 0.0f + positionZ));
            mat4 Rotation = rotate(mat4(1.0F), 0.0f, vec3(1.0F, 0.0F, 0.0F));
            mat4 Scaling = scale(mat4(1.0F), vec3(1.0F, 1.0F, 1.0F));

            mat4 Model = Translation * Rotation * Scaling * mat4(1.0f);

            // Our ModelViewProjection : multiplication of our 3 matrices
            mat4 mvp = Projection * View * Model;

            MatrixID = glGetUniformLocation(programID, "MVP");
            TextureLocId = glGetUniformLocation(programID, "myTextureSampler");

            // Send our transformation to the currently bound shader, in the "MVP" uniform
            // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

            // Draw the cube
            cube.makeCube(TextureLocId, &texture);

            // Put in the array of cube
            cubesArray.push_back(cube);

            positionZ -= 4;

        }

        /* --------------------------------------------- TRIANGLE ----------------------------------------------------------------- */

/*
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
        glDisableVertexAttribArray(0);
        */


        SDL_GL_SwapWindow(win);
    }

    return 0;
}