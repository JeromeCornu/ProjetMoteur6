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
		glm::vec3 position = glm::vec3(10, 10, -5);

		glm::vec3 direction;

		glm::vec3 up;

		glm::vec3 Right;

		std::chrono::steady_clock::time_point currentTime;

		std::chrono::duration<float> deltaTime;

		// horizontal angle : toward -Z
		float horizontalAngle = 3.14f;

		float mouseSpeed = 0.05f;

		// vertical angle : 0, look at the horizon
		float verticalAngle = 0.0f;

		float FoV;

		// Initial Field of View
		float initialFoV = 45.0f;

		float speed = 100.0f;



		void ComputeMatricesFromInputs(GLfloat Width, GLfloat Height, SDL_Window* Win);

		glm::mat4 GetProjectionMatrix();

		glm::mat4 GetViewMatrix();

		void Move(SDL_Keycode Type);
	};
}