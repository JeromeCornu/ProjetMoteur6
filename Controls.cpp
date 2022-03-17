/*#include "GL/glew.h"
#include "dep/glm/glm/glm.hpp"
#include "dep/glm/glm/ext.hpp"
#include "Controls.hpp"
#include <minwindef.h>

using namespace glm;

using namespace GC_3D;


vec3 position = vec3(0, 0, 5);

vec3 direction;

vec3 up;
// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

double currentTime = 0;

float FoV;

void Controls::ComputeMatricesFromInputs(GLuint Width, GLuint Height) {
	int xpos, ypos;
	xpos = LOWORD(&xpos);
	ypos = HIWORD(&ypos);

	glutWarpPointer(Width / 2, Height / 2);

	double lastTime = currentTime;
	currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	horizontalAngle += mouseSpeed * deltaTime * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * float(768 / 2 - ypos);

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

	if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}

	FoV = initialFoV - 5 * glfwGetMouseWheel();
}

mat4 Controls::GetProjectionMatrix() {
	return perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
}

mat4 Controls::GetViewMatrix() {
	return lookAt(
		position,				// Camera is here
		position + direction,	// and looks here : at the same position, plus "direction"
		up						// Head is up (set to 0,-1,0 to look upside-down)
	);
}*/