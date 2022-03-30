#include "FPSCounter.hpp"
#include <time.h>
#include <stdio.h>
#include <SDL_video.h>
#include <iostream>

using namespace GC_3D;
using namespace std;

void FPSCounter::Increment(SDL_Window* Win)
{
    if (clock() - t > CLOCKS_PER_SEC)
    {
        char str[50] = "";
        sprintf(str, "Moteur OpenGl - FPS : %u", fps);
        SDL_SetWindowTitle(Win, str);
        t = clock();
        fps = 0;
    }
    fps++;
}