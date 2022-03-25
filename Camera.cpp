#include "Camera.hpp"
#include <glm/ext.hpp>
#include <iostream>

using namespace glm;
using namespace GC_3D;
using namespace std;
using namespace chrono;

void Camera::ComputeMatricesFromInputs(GLfloat Width, GLfloat Height, SDL_Window* Win)
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

mat4 Camera::GetProjectionMatrix()
{
	return mat4(perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 5002.0f));
}

mat4 Camera::GetViewMatrix()
{
	return mat4(lookAt(
		position,				// Camera is here
		position + direction,	// and looks here : at the same position, plus "direction"
		up						// Head is up (set to 0,-1,0 to look upside-down)
	));
}

void Camera::Move(SDL_Event Event)
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_Z]) {
		cout << "keystates : " << keystates << endl;
	}
	if (keystates[SDL_SCANCODE_RIGHT]) {
		
	}

	if (Event.type == SDL_KEYDOWN)
	{
		switch (Event.key.keysym.sym)
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
	else if (Event.type == SDL_KEYUP)
	{
		switch (Event.key.keysym.sym)
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
		}
	}
	if (ZPressed)
	{
		position += direction * deltaTime.count() * speed;
	}
	if (SPressed)
	{
		position -= direction * deltaTime.count() * speed;
	}
	if (QPressed)
	{
		position -= Right * deltaTime.count() * speed;
	}
	if (DPressed)
	{
		position += Right * deltaTime.count() * speed;
	}
}