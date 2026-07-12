#ifndef FACTORY_H
#define FACTORY_H
#include "Components/sprite.h"
#include "Components/transform.h"
#include "world.h"
#include <SDL3/SDL_render.h>

class Factory
{
  public:
    Factory(World& in_world, SDL_Renderer* in_renderer) : world(in_world), renderer(in_renderer)
    {
    }

    void CreatePlayer()
    {
        Entity e = world.em.CreateEntity();
        // Compoenents Registery
        world.cm.RegisterComponent<Transform>();
        world.cm.RegisterComponent<Sprite>();
        // Components Creation
        Transform pTransform;
        pTransform.pos = Vec2(0.0f, 0.0f);

        Sprite pSprite;
        pSprite.texture.LoadTexture("../../assets/player/Player_Base.png", renderer);
        // Adding Components To entity
        world.cm.AddEntityComponent<Transform>(std::move(pTransform), e);
        world.cm.AddEntityComponent<Sprite>(std::move(pSprite), e);
    }

  private:
    World& world;
    // this class is not the owner of renderer dont delete it here
    SDL_Renderer* renderer;
};
#endif
