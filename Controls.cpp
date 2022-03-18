#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Controls.hpp"
#include <chrono>
#include <iostream>

using namespace glm;
using namespace std;
using namespace chrono;
using namespace GC_3D;


vec3 position = vec3(10, 10, -5);

vec3 direction = -position;

vec3 up;
// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.05f;

steady_clock::time_point currentTime;

float FoV;

void Controls::ComputeMatricesFromInputs(GLuint Width, GLuint Height, SDL_Window* Win)
{
	int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);

	SDL_WarpMouseInWindow(Win, Width / 2, Height / 2);

	auto lastTime = currentTime;
	currentTime = steady_clock::now();
	duration<float> deltaTime = currentTime - lastTime;

	horizontalAngle += mouseSpeed * deltaTime.count() * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * deltaTime.count() * float(768 / 2 - ypos);

	direction = vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	vec3 right = vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	up = cross(right, direction);

	SDL_Event curEvent;

	while (SDL_PollEvent(&curEvent))
	{
		if (curEvent.type == SDLK_z)
		{
			position += direction * deltaTime.count() * speed;
		}
		else if (curEvent.type == SDLK_s)
		{
			position -= direction * deltaTime.count() * speed;
		}
		else if (curEvent.type == SDLK_d)
		{
			position += right * deltaTime.count() * speed;
		}
		else if (curEvent.type == SDLK_q)
		{
			position -= right * deltaTime.count() * speed;
		}
	}

	FoV = initialFoV - 5 * curEvent.wheel.y;
}

mat4 Controls::GetProjectionMatrix()
{
	return mat4(perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f));
}

mat4 Controls::GetViewMatrix()
{
	return mat4(lookAt(
		position,				// Camera is here
		position + direction,	// and looks here : at the same position, plus "direction"
		up						// Head is up (set to 0,-1,0 to look upside-down)
	));
}
