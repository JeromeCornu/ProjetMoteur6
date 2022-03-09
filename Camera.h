#pragma once
<<<<<<< Updated upstream
class Camera
{
	void updateCam();
};
=======
#include "gc_3d_defs.hpp"

namespace GC_3D
{
	class Camera
	{
	private:
		vec3 Position;
		vec3 Direction;
		mat4 view;
	public:
		Camera();
	};
}
>>>>>>> Stashed changes

