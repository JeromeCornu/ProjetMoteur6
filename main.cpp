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
#include "ImGuiTool.hpp"

#include <iostream>
#include <filesystem>
#include "PathFinder.hpp"

using namespace std;
using namespace glm;
using namespace GC_3D;


int main(int argc, char* argv[])
{
    ImguiTool Imgui;
    CubeTuto Cube = CubeTuto();
    Texture Texture;

    int decrementer = 0;

    // Imgui parameters
    int NumberCubes = 5;
    float RotateX = 0.0f;
    float RotateY = 0.0f;
    float RotateZ = 0.0f;

    /* ------------------------------------------------- INITIALIZATION PathFinder ------------------------------------------------------------- */

    filesystem::path appPath(GetAppPath());
    auto appDir = appPath.parent_path();
    auto shaderPath = appDir / "asset";
    auto vShaderPath = shaderPath / "SimpleVertexShader.glsl";
    auto fShaderPath = shaderPath / "SimpleFragmentShader.glsl";

    /* --------------------------------------------- INITIALIZATION PROJECT ------------------------------------------------------------- */

    SDL_Window* Win = Init::CreateTheWindow(Imgui);
    Init::Vertex();
    GLuint ProgramID = Init::LinkShader();

    /* --------------------------------------------- INITIALIZATION CREATIONS --------------------------------------------------------- */

    // initialize cube
    Cube.initializeCube();
    // initialize texture
    Texture.applyTexture(500, 500, 1, "asset/uwu.jpg");


    auto PrevTime = std::chrono::steady_clock::now();


    /* --------------------------------------------- INITIALIZATION TABLEAU --------------------------------------------------------- */

    vector<CubeTuto> CubesArray;

    /* --------------------------------------------------- START LOOP ----------------------------------------------------------- */

    bool AppRunning = true;
    while (AppRunning)
    {

        SDL_Event CurEvent;

        while (SDL_PollEvent(&CurEvent))
        {
            ImGui_ImplSDL2_ProcessEvent(&CurEvent);

            if (CurEvent.type == SDL_QUIT || SDL_WINDOWEVENT) {

                if (CurEvent.window.event == SDL_WINDOWEVENT_CLOSE && CurEvent.window.windowID == SDL_GetWindowID(Win))
                {
                    AppRunning = false;
                }
            }

            if (CurEvent.window.type == SDL_WINDOWEVENT_RESIZED)
            {
                //glViewport(0.0, 0.0, width, height);
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Clear the screen
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

        /* --------------------------------------------------- IMGUI ------------------------------------------------------------ */
        
        Imgui.NewFrame(Win);
        Imgui.Window(&NumberCubes, &RotateX, &RotateY, &RotateZ);

        /* ---------------------------------------------------- FPS ------------------------------------------------------------- */

        FPS Fps;
        Fps.Display(Win);

        /* --------------------------------------------------- LIGHT ---------------------------------------------------------------- */

        int LightPositionID;
        LightPositionID = glGetUniformLocation(ProgramID, "LightPosition_worldspace");

        glUniform3f(LightPositionID, 5, 5, 5); // Mettre la position de la light

        /* ------------------------------------------------- BOUCLE ------------------------------------------------------------- */

        Matrix matrix;
        GLuint TextureLocId;
        mat4 Model;

        for (int i = 0; i < NumberCubes; i++)
        {
            // Contruction du cube
            mat3 TransformCube = mat3(
                {1, decrementer, 1},            // position
                {RotateX, RotateY, RotateZ},    // rotation
                {1, 1, 1}                       // scale
            );

            Cube.SetTransform(TransformCube, Model);

            // Create matrix
            matrix.ModelViewMaker(Model);
            matrix.ModelViewSetter(ProgramID, TextureLocId, Model);

            // Draw the cube
            Cube.makeCube(TextureLocId, &Texture);

            // Put in the array of cube
            CubesArray.push_back(Cube);


            decrementer -= 4;
        }

        SDL_GL_SwapWindow(Win);
    }

    Imgui.EndUi();
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