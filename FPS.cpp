#include "FPS.hpp"
#include <chrono>

using namespace GC_3D;

void FPS::Display(SDL_Window* Win)
{
    // Affichage des FPS
    static unsigned int Fps = 0;
    static clock_t T = clock();
    if (clock() - T > CLOCKS_PER_SEC)
    {
        char Str[50] = "";
        sprintf(Str, "Moteur / Groupe BRUHAHAN - FPS : %u", Fps);
        SDL_SetWindowTitle(Win, Str);
        T = clock();
        Fps = 0;
    }
    Fps++;
}