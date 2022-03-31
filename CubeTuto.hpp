#include "gc_3d_defs.hpp"

using namespace std;
using namespace glm;
using namespace GC_3D;

namespace GC_3D
{
    class Camera;

    class Texture;

    class CubeTuto
    {

        Texture* m_Texture;

    public:
        void initializeCube() const;
        void MakeCube(GLuint iTexLoc, Texture* iTex) const;
        void SetTransform(mat3 Transform, mat4& Model);
        void MakeGiantCube(Camera MainCamera, GLuint Program, Texture TextureCube, std::chrono::steady_clock::time_point PrevTime, int NumberCubes, int NumberGiantCubes);
        mat3 GetTransform();
    };

}