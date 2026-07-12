#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include "../world.h"
#include "SDL3/SDL.h"

class InputSystem
{
  public:
    InputSystem(World& in_world) : world(in_world)
    {
        SDL_zero(e);
    }

    void Update()
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        }
    }

    bool GetQuitState()
    {
        return quit;
    }

  private:
    World& world;
    SDL_Event e;
    bool quit = false;
};
#endif
