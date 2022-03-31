#include "camera.hpp"
#include <glm/ext.hpp>
#include <iostream>
#include "gc_3d_defs.hpp"

using namespace glm;
using namespace GC_3D;
using namespace std;
using namespace chrono;

Camera::Camera() {

	position = vec3(0, 0, 0);
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	initialFoV = 45.0f;
	mouseSpeed = 0.05f;
	speed = 50.0f;
}

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
	return mat4(perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 6000.0f));
}

mat4 Camera::GetViewMatrix()
{
	return mat4(lookAt(
		position,				// Camera is here
		position + direction,	// and looks here : at the same position, plus "direction"
		up						// Head is up (set to 0,-1,0 to look upside-down)
	));
}

void Camera::SetViewMatrix(vec3 NewPosition)
{
	position = NewPosition;
}

void Camera::Move(Vector<GLboolean> PressedButtons)
{
	if (PressedButtons[0])
	{
		position += direction * deltaTime.count() * speed;
	}
	if (PressedButtons[1])
	{
		position -= direction * deltaTime.count() * speed;
	}
	if (PressedButtons[2])
	{
		position -= Right * deltaTime.count() * speed;
	}
	if (PressedButtons[3])
	{
		position += Right * deltaTime.count() * speed;
	}
}