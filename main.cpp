
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <filesystem>

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
#include "Skybox.hpp"
#include "PathFinder.hpp"
#include "objLoader.hpp"
#include "Mesh.h"

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
    Skybox Sky;

    CubeTuto Cube = CubeTuto();
    CubeTuto SkyCube = CubeTuto();
    vector<CubeTuto> CubesArray;

    GLuint TextureLocId;

    Texture TextureCube;
    Texture TextureSky;
    Texture TextureModel;

    Matrix matrix;
    mat4 Model;
    mat4 ModelSky;


    // Imgui parameters
        // - Cubes
    int NumberCubes = 5;
    float RotateX = 1.0f;
    float RotateY = 1.0f;
    float RotateZ = 1.0f;
        // - Light
    float ColorLightX = 1.0f;
    float ColorLightY = 1.0f;
    float ColorLightZ = 1.0f;
    float PowerLight = 20.0f;


    /* ------------------------------------------ INITIALIZATION PATHFINDER ------------------------------------------------------------- */

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

    glUseProgram(ProgramDrawID);

    /* --------------------------------------------- INITIALIZATION BUFFERS --------------------------------------------------------- */

    // Initialize cube
    Cube.initializeCube();

    // Initialize sphere
    /*
    Geometry Sphere;
    Sphere.MakeSphere(5);
    Sphere.Bind();
    */

    /* ------------------------------------------------ ASSIMP LOADING --------------------------------------------------------- */

    Mesh Mesh;
    Vector<vec3> vertices;
    Vector<vec3> normals;
    Vector<vec2> uvs;
    Vector<unsigned int> indices;


    bool ModelLoaded = loadAssImp("asset/OldCabin/Old Cabin 3D Model.fbx", indices, vertices, uvs, normals);
    if (ModelLoaded)
    {
        Mesh.InitBuffers(vertices, uvs, normals, indices);
        // Mesh.initializeMesh();
    }

    /* --------------------------------------------------- INPUT CAMERA ----------------------------------------------------------- */

	Camera Camera;
    Camera.direction = -Camera.position;

    int ScreenWidth = 1024;
    int ScreenHeight = 768;
    
    SDL_WarpMouseInWindow(Win, ScreenWidth / 2, ScreenHeight / 2);

    bool appRunning = true;

    // Inputs 
    SDL_ShowCursor(SDL_DISABLE);

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

    /* ---------------------------------------------------- TEXTURES --------------------------------------------------------- */

    // Sky
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


    // Cube
    TextureCube.applyTexture(500, 500, 1, "asset/uwu.jpg");


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
            Camera.ComputeMatricesFromInputs(ScreenWidth, ScreenHeight, Win);
        }

        Vector<GLboolean> PressedButtons = {ZPressed, SPressed, QPressed, DPressed};

        Camera.Move(PressedButtons);

        /* ---------------------------------------------------- FPS ------------------------------------------------------------- */

        FPS Fps;
        Fps.Display(Win);

        /* ------------------------------------------------- BOUCLE ------------------------------------------------------------- */


        /*if (ModelLoaded)
        {
            mat3 TransformModel = mat3(
                { 1, 1, 1 },    // position
                { 1, 1, 1 },              // rotation
                { 1, 1, 1 }               // scale
            );
            Mesh.SetTransform(TransformModel, Model);

            // Create matrix
            matrix.ModelViewMaker(Model, Camera);
            matrix.ModelViewSetter(ProgramID, TextureLocId, Model);

            // Draw the Mesh
            Mesh.makeMesh(TextureLocId, &TextureModel, indices);
        }*/

        int PositionY = 0;

        for (int i = 0; i < NumberCubes; i++)
        {

            /* ------------------------------------------------- SKYBOX ------------------------------------------------------------- */
            
            glUseProgram(ProgramSkyID);

            glDepthMask(GL_FALSE);
            //skyboxShader.use();

            // Contruction de la Transform
            mat3 TransformSky = mat3(
                { 1, 1, 1 },                    // position
                { 1, 1, 1 },                    // rotation
                { 1, 1, 1 }                     // scale
            );

            Cube.SetTransform(TransformSky, ModelSky);
            
            matrix.ModelViewMaker(ModelSky, Camera); // View
            matrix.ModelViewSetter(ProgramSkyID, cubemapTexture, ModelSky);
            
            //glBindVertexArray(skyboxVAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthMask(GL_TRUE);


            Cube.makeCube(cubemapTexture, &TextureSky); // Draw


            /* -------------------------------------------------- CUBE ------------------------------------------------------------- */
            
            glUseProgram(ProgramDrawID);

            // Contruction du cube
            mat3 TransformCube = mat3(
                { 0, PositionY, 0 },            // position
                { RotateX, RotateY, RotateZ },  // rotation
                { 1, 1, 1 }                     // scale
            );

            Cube.SetTransform(TransformCube, Model);
            
            matrix.ModelViewMaker(Model, Camera); // View
            matrix.ModelViewSetter(ProgramDrawID, TextureLocId, Model);
            
            Cube.makeCube(TextureLocId, &TextureCube); // Draw

            // Put in the array of cube
            CubesArray.push_back(Cube);

            PositionY -= 4;
        }

        /* --------------------------------------------------- IMGUI ------------------------------------------------------------ */

        Imgui.NewFrame(Win);
        Imgui.Window(&NumberCubes, &RotateX, &RotateY, &RotateZ, &Camera, &ColorLightX, &ColorLightY, &ColorLightZ, &PowerLight);

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


/* Sky
    programme
    geométrie
    paramètre (View, proj, cubemap)
    rendu

    //Cubes
    x programme   =  Init::LinkShader
    ~ paramètre (light, view, proj, diffuseTexture)
        x = matrix.ModelViewMaker + matrix.ModelViewSetter
        ? light juste en dessous
        x TextureCube.applyTexture

    x geométrie   =  CubeTuto::SetTransform
    x positions   =  CubeTuto::SetTransform
    x rendu       =  CubeTuto::makeCube

*/





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