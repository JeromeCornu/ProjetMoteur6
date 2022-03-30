#include "Init.hpp"
#include "loadShader.hpp"
#include "ImGuiTool.hpp"

using namespace std;
using namespace glm;
using namespace GC_3D;


SDL_Window* Init::CreateTheWindow(ImguiTool& Imgui) {

    SDL_Init(SDL_INIT_VIDEO);
    uint32_t WindowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


    SDL_Window* Win = SDL_CreateWindow("Moteur - Groupe BRUHAHAN",
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

    glViewport(0, 0, 1024, 768);

    Imgui.Setup(Win, Context);

    return Win;
}

void Init::Vertex() {

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

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
}

GLuint Init::LinkShader(filesystem::path Vertex, filesystem::path Fragment) {
    GLuint ProgramID = loadShader::LoadShaders(Vertex, Fragment);
    glUseProgram(ProgramID);

    return ProgramID;
}
