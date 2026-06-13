#include "Logger/logger.h"
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>

int main()
{
    Logger::Warn("Hi");
    Logger::Info("this is info");
    Logger::Error("ERRROOOR");
    return 0;
}