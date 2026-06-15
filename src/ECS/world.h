#ifndef WORLD_H
#define WORLD_H
#include "component.h"
#include "entity.h"
#include <memory>
#include <vector>

class World
{
  public:
    World();
    void AddEntity(Entity& in_entity);
    void RemoveEntity();

  private:
    std::vector<std::unique_ptr<ComponentI>> componentsList;
};
#endif