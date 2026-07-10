#ifndef WORLD_H
#define WORLD_H
#include "componentManager.h"
#include "entityManager.h"

class World
{
  public:
    World(int initNumberOfEntity) : em(initNumberOfEntity)
    {
    }

  public:
    ComponentManager cm;
    EntityManager em;
};
#endif
