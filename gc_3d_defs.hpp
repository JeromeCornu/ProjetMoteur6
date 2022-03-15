#pragma once 

#include <chrono>

#include <glm/ext.hpp>
#include <glm/glm.hpp>  

#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>

#include <vector>;

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
}