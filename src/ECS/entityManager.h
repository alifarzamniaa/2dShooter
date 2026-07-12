#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "entity.h"
#include <stddef.h>
#include <vector>

// TODO(ali-farzamnia): for now, entities are just created increamnetally, it should be a system where
// entities can occupy the space of destroyed entity and re-use their ids.
class EntityManager
{

    const Entity NULL_ENTITY = -1;

  public:
    EntityManager(int in_numberOfEntities)
    {

        for (size_t i = 0; i < in_numberOfEntities; i++)
        {

            entities.push_back(NULL_ENTITY);
        }
    }

    Entity CreateEntity()
    {
        Entity e;
        aliveEntities.push_back(entityIds);
        entities[entityIds] = aliveEntities.size() - 1;
        e.id = entityIds++;
        return e;
    }

    void RemoveEntity(const Entity& e)
    {
        Entity densePos = entities[e.id];
        if (densePos == aliveEntities.size() - 1)
        {
            aliveEntities.pop_back();
            entities[e.id] = NULL_ENTITY;
        }
        else
        {
            entities[aliveEntities[aliveEntities.size() - 1].id] = densePos;
            aliveEntities[densePos.id] = aliveEntities[aliveEntities.size() - 1];
            aliveEntities.pop_back();
            entities[e.id] = NULL_ENTITY;
        }
    }

    std::vector<Entity>& GetEntity()
    {
        return aliveEntities;
    }

  private:
    size_t entityIds = 0;
    // spars
    std::vector<Entity> entities;
    // dense
    std::vector<Entity> aliveEntities;
};
#endif // !ENTITY_MANAGER_H
