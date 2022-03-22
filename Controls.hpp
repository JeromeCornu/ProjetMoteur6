#include "glm/glm.hpp"

struct SDL_Window;

namespace GC_3D
{
	class Controls
	{
	public:
		glm::vec3 position = glm::vec3(10, 10, -5);

		glm::vec3 direction;

		glm::vec3 up;

		glm::vec3 Right;

		void ComputeMatricesFromInputs(GLfloat Width, GLfloat Height, SDL_Window* Win);

		void Move(SDL_Keycode Type);

		glm::mat4 GetProjectionMatrix();

		glm::mat4 GetViewMatrix();
	};
}