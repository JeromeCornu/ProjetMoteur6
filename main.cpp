#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "gc_3d_defs.hpp"

#include "loadShader.hpp"
#include "CubeTuto.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "FPS.hpp"

#include <iostream>

using namespace std;
using namespace glm;
using namespace GC_3D;


int main(int argc, char* argv[])
{

    /* ------------------------------------------------- INITIALIZATION PROJECT ------------------------------------------------------------- */

    SDL_Init(SDL_INIT_VIDEO);
    uint32_t WindowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


    SDL_Window* Win = SDL_CreateWindow("Moteur - Groupe 1",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        WindowsFlags);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    SDL_GLContext Context = SDL_GL_CreateContext(Win);
    SDL_GL_MakeCurrent(Win, Context);

    glewInit();

    auto PrevTime = std::chrono::steady_clock::now();

    glViewport(0, 0, 1024, 768);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat G_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    GLuint Vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &Vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, Vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(G_vertex_buffer_data), G_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint ProgramID = loadShader::LoadShaders("C:\\Users\\jcornu\\Documents\\GitHub\\ProjetMoteur6\\SimpleVertexShader.glsl", "C:\\Users\\jcornu\\Documents\\GitHub\\ProjetMoteur6\\SimpleFragmentShader.glsl");
    glUseProgram(ProgramID);


    /* --------------------------------------------- INITIALIZATION CREATIONS --------------------------------------------------------- */

    CubeTuto Cube;
    Texture Texture;
    Camera Camera;

    // initialize cube
    Cube.initializeCube();
    // initialize texture
    Texture.applyTexture(500, 500, 1, "C:\\Users\\jcornu\\Pictures\\uwu.jpg");

    /* --------------------------------------------- INITIALIZATION TABLEAU --------------------------------------------------------- */

    vector<CubeTuto> CubesArray;

    /* --------------------------------------------------- START LOOP ----------------------------------------------------------- */

    // Nb cube wish
    int Count = 0;

    cout << "Saisir le nombre de cube voulu : ";
    cin >> Count;
    cout << "On affiche " << Count << " cube(s)." << endl;


    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    bool AppRunning = true;
    while (AppRunning)
    {
        // Position of each cube - initialization
        float PositionX = 0;
        float PositionY = 0;
        float PositionZ = 0;

        SDL_Event CurEvent;
        /*int width, height;
        SDL_GetWindowSize(win, &width, &height);

        float ratio = width / (float)height;

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);*/

        while (SDL_PollEvent(&CurEvent))
        {
            if (CurEvent.type == SDL_QUIT)
            {
                AppRunning = false;
            }

            if (CurEvent.window.type == SDL_WINDOWEVENT_RESIZED)
            {
                //glViewport(0.0, 0.0, width, height);
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Clear the screen
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

        /* ---------------------------------------------------- FPS ------------------------------------------------------------- */

        FPS Fps;
        Fps.Display(Win);


        /* ------------------------------------------------- MATRICES 1 ------------------------------------------------------------- */


        mat4 View = Camera.Create(10, 5, 10);


        /* --------------------------------------------------- LIGHT ---------------------------------------------------------------- */

        int LightPositionID;
        LightPositionID = glGetUniformLocation(ProgramID, "LightPosition_worldspace");

        glUniform3f(LightPositionID, 5, 5, 5); // Mettre la position de la light

        /* ------------------------------------------------- MATRICES 2 ------------------------------------------------------------- */

        // Position of the cube
        GLuint MatrixID;
        GLuint ViewID;
        GLuint ModelID;
        GLuint TextureLocId;
        int decrementer = 0;

        for (int i = 0; i < Count; i++)
        {
            // Chrono pour les cubes
            auto CurTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> FTime = CurTime - PrevTime;
            float Turn = sin(FTime.count());

            // Contruction du cube
            mat3 TransformCube = mat3(
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
            );

            mat4 Model = Cube.SetTransform(TransformCube);
            decrementer -= 4;

            // Projection
            mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

            // Our ModelViewProjection : multiplication of our 3 matrices
            mat4 mvp = Projection * View * Model;

            MatrixID = glGetUniformLocation(ProgramID, "MVP");
            ViewID = glGetUniformLocation(ProgramID, "View");
            ModelID = glGetUniformLocation(ProgramID, "Model");
            TextureLocId = glGetUniformLocation(ProgramID, "MyTextureSampler");

            // Send our transformation to the currently bound shader, in the "MVP" uniform
            // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
            glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);
            glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);

            // Draw the cube
            Cube.makeCube(TextureLocId, &Texture);

            // Put in the array of cube
            CubesArray.push_back(Cube);

        }

        SDL_GL_SwapWindow(Win);
    }

    return 0;
}