#pragma once

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"
#include "gc_3d_defs.hpp"
#include "Camera.hpp"
#include <SDL.h>

namespace GC_3D
{
	class ImguiTool
	{
	public:
		void Setup(SDL_Window* win, SDL_GLContext context);
		void NewFrame(SDL_Window* win);
		void Window(int* NumberCubes, float* RotateX, float* RotateY, float* RotateZ, Camera* MainCamera, float* LightColorX, float* LightColorY, float* LightColorZ, float* LightPower, float* Speed);
		bool ColorPicker(const char* label, float col[3]);
		void EndUi();
	};
}