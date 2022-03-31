#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "gc_3d_defs.hpp"

#include "Init.hpp"
#include "CubeTuto.hpp"
#include "Camera.hpp"
#include "FPS.hpp"
#include "Matrix.hpp"
#include "ImGuiTool.hpp"
#include "Skybox.hpp"

#include <iostream>
#include <filesystem>
#include "PathFinder.hpp"
#include "Ship.hpp"
#include "objLoader.hpp"
#include "Mesh.h"

#define SHIP_COLOR_BLUE "Blue"
#define SHIP_COLOR_GREEN "Green"
#define SHIP_COLOR_ORANGE "Orange"
#define SHIP_COLOR_PURPLE "Purple"
#define SHIP_COLOR_RED "Red"

using namespace glm;
using namespace std;
using namespace chrono;
using namespace GC_3D;



extern "C" {
    _declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
}


int main(int argc, char* argv[])
{
	
    ImguiTool Imgui;
    CubeTuto Cube = CubeTuto();
    Texture TextureCube;
    Skybox Sky;



    // Imgui parameters
    int NumberCubes = 5;
    int NumberGiantCubes = 2;
    float RotateX = 1.0f;
    float RotateY = 1.0f;
    float RotateZ = 1.0f;

    /* ------------------------------------------------- INITIALIZATION PathFinder ------------------------------------------------------------- */


    filesystem::path appPath(GetAppPath());
    auto appDir = appPath.parent_path();
    auto shaderPath = appDir / "asset";
    auto vShaderPath = shaderPath / "SimpleVertexShader.glsl";
    auto fShaderPath = shaderPath / "SimpleFragmentShader.glsl";
    auto vSkyboxPath = shaderPath / "SkyboxVertexShader.glsl";
    auto fSkyboxPath = shaderPath / "SkyboxFragmentShader.glsl";

    /* --------------------------------------------- INITIALIZATION PROJECT ------------------------------------------------------------- */


    SDL_Window* Win = Init::CreateTheWindow(Imgui);
    Init::Vertex();
    GLuint ProgramID = Init::LinkShader(vShaderPath, fShaderPath);


    /* --------------------------------------------- INITIALIZATION CREATIONS --------------------------------------------------------- */

    // initialize cube
    Cube.initializeCube();
    // initialize texture
    TextureCube.applyTexture(500, 500, 1, "asset/uwu.jpg");

    // Skybox
    Sky.SkyBox_CreateTexture();


    vector<std::string> faces;
    {
            "right.jpg",
            "left.jpg",
            "top.jpg",
            "bottom.jpg",
            "front.jpg",
            "back.jpg";
    };
    unsigned int cubemapTexture = Sky.loadCubemap(faces);


	// initialize sphere
    /*
    Geometry Sphere;
    Sphere.MakeSphere(5);
    Sphere.Bind();
    */

    auto PrevTime = std::chrono::steady_clock::now();



    /* ------------------------------------------------------- SKYBOX --------------------------------------------------------------- */

    glDepthMask(GL_FALSE);
    //skyboxShader.use();
    // ... set view and projection matrix
    //glBindVertexArray(skyboxVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
    // ... draw rest of the scene


    /* --------------------------------------------- INITIALIZATION TABLEAU --------------------------------------------------------- */


    vector<CubeTuto> CubesArray;



    /* --------------------------------------------- ASSIMP LOADING --------------------------------------------------------- */

    Mesh MeshEarth;
    /*Mesh MeshSpitfire;
    Mesh MeshBob;
    Mesh MeshChallenger;
    */

    Texture TextureEarth;
    /*Texture TextureSpitfire;
    Texture TextureBob;
    Texture TextureChallenger;
    */
    Vector<vec3> vertices;
    Vector<vec2> uvs;
    Vector<vec3> normals;

    Vector<unsigned int> indicesEarth;
    /*
    Vector<unsigned int> indicesSpitfire;
    Vector<unsigned int> indicesBob;
    Vector<unsigned int> indicesChallenger;
    */

    Vessel Bob;
    Bob.InitShip("Bob", SHIP_COLOR_ORANGE);

    TextureEarth.applyTexture(4096, 4096, 1, "asset/Earth/textures/earth albedo.jpg");
    
    bool EarthModelLoaded = loadAssImp("asset/Earth/earth 2.blend", indicesEarth, vertices, uvs, normals);
    MeshEarth.InitBuffers(vertices, uvs, normals, indicesEarth);

    /* --------------------------------------------------- INPUT CAMERA ----------------------------------------------------------- */

	Camera Camera;
    Camera.direction = -Camera.position;

    int ScreenWidth = 1024;
    int ScreenHeight = 768;
    
    SDL_WarpMouseInWindow(Win, ScreenWidth / 2, ScreenHeight / 2);

    bool appRunning = true;
    SDL_ShowCursor(SDL_DISABLE);

    bool ZPressed = false;

    bool SPressed = false;

    bool DPressed = false;

    bool QPressed = false;


    bool ControlMouse = false;

    /* --------------------------------------------------- LIGHT ---------------------------------------------------------------- */

    int LightPositionID;
    LightPositionID = glGetUniformLocation(ProgramID, "LightPosition_worldspace");


    int LightPowerID;
    LightPowerID = glGetUniformLocation(ProgramID, "LightPower");

    int LightColorID;
    LightColorID = glGetUniformLocation(ProgramID, "LightColor");

    float ColorLightX = 1.0f;
    float ColorLightY = 1.0f;
    float ColorLightZ = 1.0f;
    float PowerLight = 20;


    /* --------------------------------------------------- START LOOP ----------------------------------------------------------- */

    bool AppRunning = true;
    while (AppRunning)
    {
        SDL_Event CurEvent;

        while (SDL_PollEvent(&CurEvent))
        {
            ImGui_ImplSDL2_ProcessEvent(&CurEvent);

			if (CurEvent.type == SDL_KEYDOWN)
            {
                switch (CurEvent.key.keysym.sym)
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
            else if (CurEvent.type == SDL_KEYUP)
            {
                switch (CurEvent.key.keysym.sym)
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


                    // Quit application (escape)
                case SDLK_ESCAPE:
                    AppRunning = false;
                    break;

                    // Take/Lose control Mouse
                case SDLK_m:
                    ControlMouse = !ControlMouse;
                    break;
                }
            }
            // Quit application (red cross)
            if (CurEvent.type == SDL_QUIT) {
                AppRunning = false;
            }

            if (CurEvent.window.type == SDL_WINDOWEVENT_RESIZED)
            {
                // glViewport(0.0, 0.0, width, height);
            }
        }		
		
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Clear the screen
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

        /* --------------------------------------------------- PARAMETERS ------------------------------------------------------------ */


        Matrix matrix;
        GLuint TextureLocId;
        mat4 Model;
        int PositionY = 0;
		
		/* --------------------------------------------------- CAMERA ------------------------------------------------------------ */
        if (!ControlMouse) {
            Camera.ComputeMatricesFromInputs(ScreenWidth, ScreenHeight, Win);
        }

        Vector<GLboolean> PressedButtons = {ZPressed, SPressed, QPressed, DPressed};

        Camera.Move(PressedButtons);

        /* ---------------------------------------------------- FPS ------------------------------------------------------------- */

        FPS Fps;
        Fps.Display(Win);

        /* ------------------------------------------------- BOUCLE ------------------------------------------------------------- */



        Cube.MakeGiantCube(Camera, ProgramID, TextureCube, PrevTime, NumberCubes, NumberGiantCubes);

        MeshEarth.DrawMesh(Model, matrix, ProgramID, TextureLocId, TextureEarth, indicesEarth, Camera);
        //MeshSpitfire.DrawMesh(Model, matrix, ProgramID, TextureLocId, TextureSpitfire, indicesSpitfire, Camera);
        //MeshBob.DrawMesh(Model, matrix, ProgramID, TextureLocId, TextureBob, indicesBob, Camera);
        //MeshChallenger.DrawMesh(Model, matrix, ProgramID, TextureLocId, TextureChallenger, indicesChallenger, Camera);
        Bob.DrawShip(Model, matrix, ProgramID, TextureLocId, Camera);
        /* --------------------------------------------------- IMGUI ------------------------------------------------------------ */

        Imgui.NewFrame(Win);
        Imgui.Window(&NumberCubes, &NumberGiantCubes, &RotateX, &RotateY, &RotateZ, &Camera, &ColorLightX, &ColorLightY, &ColorLightZ, &PowerLight, &Camera.speed);

        /* ------------------------------------------------ LIGHT SETUP --------------------------------------------------------- */

        glUniform3f(LightPositionID, 5, 5, 5);                                  // Mettre la position de la light
        glUniform3f(LightColorID, ColorLightX, ColorLightY, ColorLightZ);       // Mettre la couleur de la light
        glUniform1f(LightPowerID, PowerLight);                                  // Mettre le power de la light

        /* --------------------------------------------------- END ------------------------------------------------------------ */

        SDL_GL_SwapWindow(Win);
    }
	
    Imgui.EndUi();

    return 0;
}


/* FRUSTUM CULLING
    Utiliser les snippets "Math" et la suite du gc_3d_defs du prof (sur le drive)
    produit scalaire = position * normal face cube =
    regarder si c'est positif ou negatif
    (on voit si c'est derriere ou devant leS faces des "cube") donc on l'affiche ou pas

        on va pas tester tt les points : donner un centre et prendre la sphere englobante
        si elle est dehors le frustum completement, alors le modele de la sphere est dehors
        Si c'est plus de - du rayon de la sphere, pb pcq elle est encore dedans
        Si c'est moins c'est nickel


    Pour trouver normal = regle de la main droite

*/