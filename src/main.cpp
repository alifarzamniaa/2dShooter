#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>

int main()
{
    std::cout << "Hello World! Old\n";
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    MIX_Init();
    return 0;
}