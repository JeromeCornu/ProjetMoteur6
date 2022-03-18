#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#endif

#include "gc_3d_defs.hpp"
#include <SDL.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include "camera.hpp"
#include "loadShader.cpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"

#include "assimp_model.h"



using namespace GC_3D;

void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    printf(message);
}


int main(int argc, char* argv[])
{
    CAssimpModel ModelLoader;
    float speed;
    bool someBoolean;
    
    /*
    Vector<vec3> Positions = { {0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1}, {1, 1, 0}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1} };
    int index[] = { 0, 1, 2, 1, 2, 4, 2, 4, 6, 4, 6, 7, 1, 4, 5, 4, 5, 7, 0, 1, 3, 1, 3, 5, 0, 2, 3, 2, 3, 6, 3, 5, 6, 5, 6, 7};
    */

    /*Positions.push_back(vec3(-1, 0, 0));
    Positions.push_back(vec3(0, 1, 0));
    Positions.push_back(vec3(1, 0, 0));*/

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);


    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);
    
    glewInit();


    glDebugMessageCallback(&glDebugOutput, nullptr);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    // window is the SDL_Window*
    // context is the SDL_GLContext
    ImGui_ImplSDL2_InitForOpenGL(win, context);
    ImGui_ImplOpenGL3_Init();

    GLuint programID = LoadShaders("D:\\Users\\Gjacot\\GroupeMoteur\\ProjetMoteur6\\common\\SimpleVertexShader.vertexshader",
        "D:\\Users\\Gjacot\\GroupeMoteur\\ProjetMoteur6\\common\\SimpleFragmentShader.fragmentshader");
    glUseProgram(programID);

    ModelLoader.DoTheImportThing("C:\\Users\\gjacot\\Downloads\\suzane.obj");

    bool apprunning = true;
    while (apprunning)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {
            ImGui_ImplSDL2_ProcessEvent(&curEvent);

            switch (curEvent.type)
            {
            case SDL_QUIT || SDL_WINDOWEVENT:
                if (curEvent.window.event == SDL_WINDOWEVENT_CLOSE && curEvent.window.windowID == SDL_GetWindowID(win))
                {
                    apprunning = false;
                }
                break;

            case SDL_MOUSEMOTION:
                printf("We got a motion event.\n");
                printf("Current mouse position is: (%d, %d)\n", curEvent.motion.x, curEvent.motion.y);
                break;
            
            case SDL_KEYDOWN:
                printf("we got a keyBoard event.\n");
                break;
            

            default:
               printf("Unhandled Event!\n");
                break;
            }


            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Render other stuff...
            // Render imgui

        }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(win);
        ImGui::NewFrame();



        glViewport(0, 0, 1024, 768);
        glClearColor(0.5f, 0.5f, 0.9f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //glColor4f(1.0, 1.0, 1.0, 1.0);
        /*glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        
        glEnd();*/
        
        
        /*        
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(vec3), Positions.data());
        */

        

        //glDrawElements(GL_TRIANGLES, Positions.size(), GL_UNSIGNED_INT, index);

        // 1st attribute buffer : vertices
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

        ImGui::Begin("MyWindow");
        ImGui::Checkbox("Boolean property", &someBoolean);
        if (ImGui::Button("Reset Speed")) {
            // This code is executed when the user clicks the button
            speed = 0;
        }
        ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(win);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}