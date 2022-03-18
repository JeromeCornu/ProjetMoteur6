#include "glm/glm.hpp"

struct SDL_Window;

namespace GC_3D
{
	class Controls
	{
	public:
		void ComputeMatricesFromInputs(GLuint Width, GLuint Height, SDL_Window* Win);

		glm::mat4 GetProjectionMatrix();

		glm::mat4 GetViewMatrix();
	};
}