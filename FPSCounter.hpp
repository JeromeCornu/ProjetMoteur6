#include <time.h>

struct SDL_Window;

namespace GC_3D
{
	class FPSCounter
	{
	public:
		unsigned int fps = 0;

		clock_t t = clock();

		void Increment(SDL_Window* Win);
	};
}