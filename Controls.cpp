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

// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 100.0f; // 3 units / second
float mouseSpeed = 0.05f;

steady_clock::time_point currentTime;

float FoV;

duration<float> deltaTime;



void Controls::ComputeMatricesFromInputs(GLfloat Width, GLfloat Height, SDL_Window* Win)
{
	int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);

	SDL_WarpMouseInWindow(Win, Width / 2, Height / 2);

	auto lastTime = currentTime;
	currentTime = steady_clock::now();
	deltaTime = currentTime - lastTime;

	float diffX = Width / 2 - xpos;
	float diffY = Height / 2 - ypos;

	if (diffX < -5 || diffX > 5)
	{
		horizontalAngle += mouseSpeed * deltaTime.count() * float(diffX);
	}
	if (diffY < -5 || diffY > 5)
	{
		verticalAngle += mouseSpeed * deltaTime.count() * float(diffY);
	}

	direction = vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	Right = vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	up = cross(Right, direction);

	SDL_Event curEvent;
	
	while (SDL_PollEvent(&curEvent))
	{
		
	}

	FoV = initialFoV - 5 * curEvent.wheel.y;
}

mat4 Controls::GetProjectionMatrix()
{
	return mat4(perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 5002.0f));
}

mat4 Controls::GetViewMatrix()
{
	return mat4(lookAt(
		position,				// Camera is here
		direction,	// and looks here : at the same position, plus "direction"
		up						// Head is up (set to 0,-1,0 to look upside-down)
	));
}

void Controls::Move(SDL_Keycode Type)
{
	switch (Type)
	{
	case SDLK_z:
		position += direction * deltaTime.count() * speed;
		break;
	case SDLK_s:
		position -= direction * deltaTime.count() * speed;
		break;
	case SDLK_d:
		position += Right * deltaTime.count() * speed;
		break;
	case SDLK_q:
		position -= Right * deltaTime.count() * speed;
		break;
	}
}