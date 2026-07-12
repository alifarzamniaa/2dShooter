#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "../Components/sprite.h"
#include "../Components/transform.h"
#include "../world.h"
#include <SDL3/SDL.h>

class RenderSystem
{
  public:
    RenderSystem(World& in_world) : world(in_world)
    {
    }

    void Update()
    {
        for (auto& e : world.em.GetEntity())
        {
            Transform* tf = world.cm.GetComponent<Transform>(e);
            Sprite* sp = world.cm.GetComponent<Sprite>(e);
            if (tf && sp)
            {
                SDL_RenderClear(world.renderer);
                SDL_FRect texRect;
                texRect.x = 0;
                texRect.y = 0;
                texRect.w = (float)48;
                texRect.h = (float)sp->texture.GetHeight();

                SDL_FRect transformRect;
                transformRect.x = tf->pos.x;
                transformRect.y = tf->pos.y;
                transformRect.w = (float)48;
                transformRect.h = (float)sp->texture.GetHeight();
                SDL_RenderTexture(world.renderer, sp->texture.GetTexture(), &texRect, &transformRect);
                SDL_RenderPresent(world.renderer);
            }
        }
    }

  private:
    std::vector<Entity> requiredEntities;
    World& world;
};
#endif
