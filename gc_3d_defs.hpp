#pragma once 

#include <chrono>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>;
#include <GL/glew.h>

namespace GC_3D
{
    using namespace glm;

    template <typename T>
    using Vector = std::vector<T>;

    using Clock = std::chrono::high_resolution_clock;
    using Timestamp = Clock::time_point;
    using Duration = Clock::duration;

    inline float Seconds(Duration const& iDuration)
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(iDuration).count();
    }

    struct BoundingSphere
    {
        vec3 m_Center;
        float m_Radius;
    };

    struct Geometry
    {
    public:
        //These arrays should all have the same size.
        //They can be empty as well
        Vector<vec3> m_Pos;      // Up
        Vector<vec3> m_Normals;
        Vector<vec2> m_TexCoord;

        Vector<uint32_t> m_Indices;

        void Bind() const;
        void Draw() const;
        Geometry MakeSphere(float iRadius);
    };
}