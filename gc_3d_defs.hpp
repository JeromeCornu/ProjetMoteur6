#pragma once

#include <chrono>

#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>
#include <string>
#include <memory>

namespace GC_3D
{
    using namespace glm;

    template <typename T>
    using Vector = std::vector<T>;

    using String = std::string;

    using Clock = std::chrono::high_resolution_clock;
    using Timestamp = Clock::time_point;
    using Duration = Clock::duration;

    template<typename T>
    using SharedPtr = std::shared_ptr<T>;

    inline float Seconds(Duration const& iDuration)
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(iDuration).count();
    }

    struct Box3D;

    struct BoundingSphere
    {
        static BoundingSphere FromBox(Box3D const& iSphere);

        vec3 m_Center;
        float m_Radius;
    };

    struct Box3D
    {
        vec3 m_Center;
        vec3 m_HalfExtent = vec3(0, 0, 0);

        static Box3D FromSphere(BoundingSphere const& iSphere)
        {
            return Box3D{ iSphere.m_Center, one<vec3>() * iSphere.m_Radius };
        }

        static Box3D FromExtremas(vec3 const& iMin, vec3 const& iMax)
        {
            return Box3D{ (iMin + iMax) * 0.5f, (iMax - iMin) * 0.5f };
        }

        bool IsEmpty() const { return m_HalfExtent == zero<vec3>(); }
        Box3D Merge(Box3D const& other) const;
        Box3D Merge(vec3 const& iPoint) const;
        vec3 Min() const { return m_Center - m_HalfExtent; }
        vec3 Max() { return m_Center + m_HalfExtent; }
    };

    inline BoundingSphere BoundingSphere::FromBox(Box3D const& iBox)
    {
        return BoundingSphere{ iBox.m_Center, length(iBox.m_HalfExtent) };
    }

    struct Plane
    {
        vec3 m_PlaneNormal;
        float m_Dist;

        static Plane FromPointAndNormal(vec3 const& iNormal, vec3 const& iPoint)
        {
            Plane plane;
            plane.m_PlaneNormal = normalize(iNormal);
            plane.m_Dist = -dot(iPoint, plane.m_PlaneNormal);

            return plane;
        }

        float SignedDistanceToPlane(vec3 const& iPoint) const
        {
            return dot(iPoint, m_PlaneNormal) + m_Dist;
        }
    };

}