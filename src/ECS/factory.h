#ifndef FACTORY_H
#define FACTORY_H
#include "Components/Transform.h"
#include "world.h"

class Factory
{
  public:
    Factory(World& in_world) : world(in_world)
    {
    }

    void CreatePlayer()
    {
        Entity e = world.em.CreateEntity();
        // Compoenents Registery
        world.cm.RegisterComponent<Transform>();
        // Components Creation
        Transform pTransform;
        pTransform.pos = Vec2(0.0f, 0.0f);
        // Adding Components To entity
        world.cm.AddEntityComponent<Transform>(pTransform, e);
    }

  private:
    World& world;
};
#endif
