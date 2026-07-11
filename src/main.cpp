#include "ECS/world.h"
#include "SDL3/SDL.h"

int main()
{
    World world(100);
    SDL_Init(SDL_INIT_VIDEO);
    return 0;
}
