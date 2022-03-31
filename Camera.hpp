#pragma once

#include "gc_3d_defs.hpp"
#include <GL/glew.h>
#include <SDL_video.h>
#include <glm/glm.hpp>
#include <SDL.h>
#include <chrono>

struct SDL_Window;

namespace GC_3D
{
	class Camera
	{
	public:
		glm::vec3 position;

		glm::vec3 direction;

		glm::vec3 up;

		glm::vec3 Right;

		std::chrono::steady_clock::time_point currentTime;

		std::chrono::duration<float> deltaTime;

		// horizontal angle : toward -Z
		float horizontalAngle;

		float mouseSpeed;

		// vertical angle : 0, look at the horizon
		float verticalAngle;

		float FoV;

		// Initial Field of View
		float initialFoV;

		float speed;

		bool ZPressed = false;

		bool SPressed = false;

		bool DPressed = false;

		bool QPressed = false;


		
		Camera();

		void ComputeMatricesFromInputs(GLfloat Width, GLfloat Height, SDL_Window* Win);

		glm::mat4 GetProjectionMatrix();

		glm::mat4 GetViewMatrix();

		void SetViewMatrix(vec3 NewPosition);

		void Move(Vector<GLboolean> PressedButtons);
	};
}