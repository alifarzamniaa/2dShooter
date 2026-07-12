#include "ECS/Systems/RenderSystem.h"
#include "ECS/factory.h"
#include "ECS/world.h"
#include "Logger/logger.h"
#include <SDL3/SDL.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        Logger::Error("could not initialize SDL");
    }

    World world(100);
    Factory factory(world, world.renderer);
    factory.CreatePlayer();
    RenderSystem render(world);
    while (true)
    {

        render.Update();
    }
    return 0;
}
