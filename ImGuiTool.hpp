#pragma once

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"
#include "gc_3d_defs.hpp"
#include <SDL.h>

namespace GC_3D
{
	class ImguiTool
	{
	public:
		void Setup(SDL_Window* win, SDL_GLContext context);
		void NewFrame(SDL_Window* win);
		void Window(float* speed, bool* someBoolean);
		void EndUi();
	};
}