#ifndef ENTITY_H
#define ENTITY_H
#include <stddef.h>

struct Entity
{
    Entity() : id(0)
    {
    }

    Entity(size_t in_id) : id(in_id)
    {
    }

    size_t id = 0;

    bool operator==(const Entity& other) const
    {
        return id == other.id;
    }

    bool operator!=(const Entity& other) const
    {
        return id != other.id;
    }
};
#endif
