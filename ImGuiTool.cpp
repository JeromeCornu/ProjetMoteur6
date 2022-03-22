
#include "ImGuiTool.hpp"


namespace GC_3D
{
    void ImguiTool::Setup(SDL_Window* win, SDL_GLContext context)
    {
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
    }

    void ImguiTool::NewFrame(SDL_Window* win)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(win);
        ImGui::NewFrame();
    }

    void ImguiTool::Window(float* speed, bool* someBoolean)
    {
        ImGui::Begin("MyWindow");

        ImGui::Checkbox("Boolean property", someBoolean);
        if (ImGui::Button("Reset Speed")) {
            // This code is executed when the user clicks the button
            *speed = 0;
        }
        ImGui::SliderFloat("Speed", speed, 0.0f, 10.0f);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImguiTool::EndUi()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
}