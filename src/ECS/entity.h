#ifndef ENTITY_H
#define ENTITY_H

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