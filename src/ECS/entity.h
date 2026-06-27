#ifndef ENTITY_H
#define ENTITY_H
#include <stddef.h>

struct Entity
{
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
