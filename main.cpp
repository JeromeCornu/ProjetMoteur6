#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif

#include "gc_3d_defs.hpp"
#include "Init.hpp"
#include "Texture.hpp"
#include "CubeTuto.hpp"
#include "Camera.hpp"
#include "FPS.hpp"
#include "Matrix.hpp"
#include "ImGuiTool.hpp"
#include "Skybox.hpp"
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
    /* ----------------------------------------------- DEFINITION DES VARIABLES ------------------------------------------------------------- */

    ImguiTool Imgui;
	
    CubeTuto Cube = CubeTuto();
    Skybox Sky;

    GLuint TextureLocId;

    Texture TextureCube;
    Texture TextureSky;
    Texture TextureModel;

    Matrix matrix;
    mat4 Model;
    mat4 ModelSky;

    Mesh SkyMesh;

	vector<CubeTuto> CubesArray;

    // Imgui parameters
        // - Cubes
    int NumberCubes = 5;
    int NumberGiantCubes = 2;
    float RotateX = 1.0f;
    float RotateY = 1.0f;
    float RotateZ = 1.0f;
        // - Light
    float ColorLightX = 1.0f;
    float ColorLightY = 1.0f;
    float ColorLightZ = 1.0f;
    float PowerLight = 20.0f;
    // - Skybox
    bool ActivateSkybox = false;


    /* --------------------------------------------------- SKYBOX VERTICES -------------------------------------------------------- */

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    /* --------------------------------------------- INITIALIZATION PATHFINDER -------------------------------------------------------- */

    glEnable(GL_DEPTH_TEST);


    filesystem::path appPath(GetAppPath());
    auto appDir = appPath.parent_path();
    auto shaderPath = appDir / "asset";
    auto vShaderPath = shaderPath / "SimpleVertexShader.glsl";
    auto fShaderPath = shaderPath / "SimpleFragmentShader.glsl";
    auto vSkyboxPath = shaderPath / "SkyboxVertexShader.glsl";
    auto fSkyboxPath = shaderPath / "SkyboxFragmentShader.glsl";

    /* --------------------------------------------- LANCEMENT PROJECT ------------------------------------------------------------- */

    SDL_Window* Win = Init::CreateTheWindow(Imgui);
    Init::Vertex();

    GLuint ProgramDrawID = Init::LinkShader(vShaderPath, fShaderPath);
    GLuint ProgramSkyID = Init::LinkShader(vSkyboxPath, fSkyboxPath);


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


    auto PrevTime = std::chrono::steady_clock::now();
	

    /* -------------------------------------------------- SKYBOX VAO ------------------------------------------------------------------ */

    unsigned int skyboxVAO, skyboxVBO;

        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    

    /* ------------------------------------------------ LOAD TEXTURE --------------------------------------------------------- */
    unsigned int cubemapTexture = Sky.LoadingTexture(appDir);

    // shader configuration
    // --------------------
    string sSky = "skybox";
    glUseProgram(ProgramSkyID);
    glUniform1i(glGetUniformLocation(ProgramSkyID, sSky.c_str()), 0);
    glUseProgram(ProgramDrawID);

    /* --------------------------------------------- ASSIMP LOADING --------------------------------------------------------- */

    Mesh MeshEarth;

    Texture TextureEarth;
	
    Vector<vec3> vertices;
    Vector<vec2> uvs;
    Vector<vec3> normals;

    Vector<unsigned int> indicesEarth;

    Vessel Bob;
    Bob.InitShip("Bob", SHIP_COLOR_ORANGE);

    TextureEarth.applyTexture(4096, 4096, 1, "asset/Earth/textures/earth albedo.jpg");
    
    bool EarthModelLoaded = loadAssImp("asset/Earth/earth 2.blend", indicesEarth, vertices, uvs, normals);
    MeshEarth.InitBuffers(vertices, uvs, normals, indicesEarth);

    /* --------------------------------------------------- INPUT CAMERA ----------------------------------------------------------- */

	Camera TheCamera;
    TheCamera.direction = -TheCamera.position;

    int ScreenWidth = 1024;
    int ScreenHeight = 768;
    
    SDL_WarpMouseInWindow(Win, ScreenWidth / 2, ScreenHeight / 2);

    // Inputs 
    SDL_ShowCursor(SDL_DISABLE);
	
    bool appRunning = true;

    bool ZPressed = false;
    bool SPressed = false;
    bool DPressed = false;
    bool QPressed = false;
    bool ControlMouse = false;
    
/* --------------------------------------------------- LIGHT ---------------------------------------------------------------- */

    int LightPositionID;
    LightPositionID = glGetUniformLocation(ProgramDrawID, "LightPosition_worldspace");


    int LightPowerID;
    LightPowerID = glGetUniformLocation(ProgramDrawID, "LightPower");

    int LightColorID;
    LightColorID = glGetUniformLocation(ProgramDrawID, "LightColor");

    /* --------------------------------------------------- START LOOP ----------------------------------------------------------- */

    bool AppRunning = true;
    while (AppRunning)
    {
        SDL_Event CurEvent;

        // Inputs
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

                    // Take/Lose control Mouse with "M"
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
		
		/* --------------------------------------------------- CAMERA ------------------------------------------------------------ */
       
        if (!ControlMouse) {
            TheCamera.ComputeMatricesFromInputs(ScreenWidth, ScreenHeight, Win);
        }

        Vector<GLboolean> PressedButtons = {ZPressed, SPressed, QPressed, DPressed};

        TheCamera.Move(PressedButtons);

        /* ---------------------------------------------------- FPS ------------------------------------------------------------- */

        FPS Fps;
        Fps.Display(Win);

        /* ------------------------------------------------- SKYBOX ------------------------------------------------------------- */
        if (ActivateSkybox) {

            glUseProgram(ProgramSkyID);
			
            // Contruction de la Transform
            mat3 TransformSky = mat3(
                { 1, 1, 1 },                    // position
                { 1, 1, 1 },                    // rotation
                { 1, 1, 1 }                     // scale
            );

            SkyMesh.SetTransform(TransformSky, ModelSky);


            // draw skybox as last
            glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content

            matrix.ModelViewMaker(ModelSky, TheCamera); // View
            matrix.ModelViewSetter(ProgramSkyID, ModelSky);


            mat4 View = glm::mat4(glm::mat3(TheCamera.GetViewMatrix())); // remove translation from the view matrix
            mat4 Projection = glm::mat4(glm::mat3(TheCamera.GetProjectionMatrix())); // remove translation from the view matrix

            string sView("view");
            int viewLoc = glGetUniformLocation(ProgramSkyID, sView.c_str());
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(View));

            string sProj("projection");
            int projLoc = glGetUniformLocation(ProgramSkyID, sProj.c_str());
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(Projection));


            // skybox
            glBindVertexArray(skyboxVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);

            glDepthFunc(GL_LESS); // set depth function back to default
        }

        /* --------------------------------------------------- IMGUI ------------------------------------------------------------ */

        Imgui.NewFrame(Win);
        Imgui.Window(&NumberCubes, &RotateX, &RotateY, &RotateZ, &TheCamera, &ColorLightX, &ColorLightY, &ColorLightZ, &PowerLight, &Camera.speed, &ActivateSkybox);


        Cube.MakeGiantCube(Camera, ProgramDrawID, TextureCube, PrevTime, NumberCubes, NumberGiantCubes);

        mat3 TransformEarth = {
            { 0, 0, 0 },
            { 1, 1, 1 },
            { 1, 1, 1 }
        };

        MeshEarth.DrawMesh(Model, matrix, ProgramDrawID, TextureLocId, TextureEarth, indicesEarth, Camera, TransformEarth);
        Bob.DrawShip(Model, matrix, ProgramDrawID, TextureLocId, Camera);
		
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