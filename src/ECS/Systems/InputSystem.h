#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include "../Components/tags.h"
#include "../Components/transform.h"
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
            if (e.type == SDL_EVENT_KEY_DOWN)
            {
                if (!hasPlayer)
                {
                    for (auto& entity : world.em.GetEntity())
                    {
                        Tag* tg = world.cm.GetComponent<Tag>(entity);
                        if (tg && tg->tag == "player")
                        {
                            player = entity;
                            hasPlayer = true;
                            break;
                        }
                    }
                }

                Transform* playertf = hasPlayer ? world.cm.GetComponent<Transform>(player) : nullptr;
                if (!playertf)
                    hasPlayer = false;
                if (e.key.key == SDLK_A && playertf)

                {
                    playertf->pos.x -= 1;
                }
                if (e.key.key == SDLK_D && playertf)
                {
                    playertf->pos.x += 1;
                }
                if (e.key.key == SDLK_W && playertf)
                {
                    playertf->pos.y -= 1;
                }
                if (e.key.key == SDLK_S && playertf)
                {
                    playertf->pos.y += 1;
                }
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
    Entity player;
    bool hasPlayer = false;
    bool quit = false;
};
#endif
