#include "Camera.hpp"
#include <chrono>

using namespace GC_3D;

mat4 Camera::Create(float PositionX, float PositionY, float PositionZ)
{
    // Or, for an ortho camera :
    //mat4 Projection = ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
    auto PrevTime = std::chrono::steady_clock::now();

    // Chrono pour la caméra
    auto CurTime = Clock::now();
        // Faire tourner la caméra :
    // std::chrono::duration<float> FTime = CurTime - PrevTime;
    // float TurnSin = sin(FTime.count());
    // float TurnCos = cos(FTime.count());

    // Position de la caméra
    vec3 CameraPosition = vec3(PositionX, PositionY, PositionZ);

    // Camera matrix
    mat4 View = lookAt(
        vec3(CameraPosition),
        vec3(0, 0, 0), // and looks at the origin
        vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    return View;
}