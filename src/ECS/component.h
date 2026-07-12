#ifndef COMPONENT_H
#define COMPONENT_H
#include "../Logger/logger.h"
#include "entity.h"
#include <unordered_map>
#include <vector>

struct ComponentI
{
    virtual ~ComponentI() {};
    virtual void RemoveEntity(const Entity& e) = 0;
};

template<typename ComponentClassType>
struct ComponentContainer : ComponentI

{
    std::vector<ComponentClassType> components;
    std::vector<int> entityIdPerIndex;
    // TODO(ali-farzamnia) : for better performance i should consider using
    // sparse or other alghoritms rather than unordered map beacuse its not
    // contigious
    std::unordered_map<int, int> componentMapping;

    void AddComponent(const ComponentClassType& in_component, const Entity& e)
    {
        // NOTE(ali-farzamnia) : to stop adding duplicate
        if (componentMapping.find(e.id) != componentMapping.end())
        {
            return;
        }
        components.push_back(in_component);
        entityIdPerIndex.push_back(e.id);
        // NOTE(ali-farzamnia) : store the index of the pushed component so we
        // can find it by -- entity id with complexity of O(1)
        componentMapping[e.id] = components.size() - 1;
    }

    void RemoveComponent(const Entity& e)
    {
        auto componentIndex = componentMapping.find(e.id);
        if (componentIndex != componentMapping.end())
        {
            // NOTE(ali-farzamnia): if already last, no swap needed
            if (componentIndex->second == components.size() - 1)
            {
                components.pop_back();
                entityIdPerIndex.pop_back();
                componentMapping.erase(e.id);
            }
            else
            {
                components[componentIndex->second] = std::move(components.back());
                components.pop_back();
                // NOTE(ali-farzamnia): swap-and-pop: move last component into
                // the deleted slot to keep the array contiguous without
                // shifting
                int lastComponentOwnerId = entityIdPerIndex.back();
                componentMapping.at(lastComponentOwnerId) = componentIndex->second;

                // NOTE(ali-farzamnia): patch up both lookup structures to
                // reflect the last component's new index
                entityIdPerIndex[componentIndex->second] = lastComponentOwnerId;
                entityIdPerIndex.pop_back();
                componentMapping.erase(e.id);
            }
        }
    }

    void Destroy()
    {
        components.clear();
        entityIdPerIndex.clear();
        componentMapping.clear();
    }

    ComponentClassType* GetComponent(const Entity& e)
    {
        // TODO(ali-farzamnia) : this check is kinda expensive, i should make it
        // return null silently instead or use assert for debug only
        auto comp = componentMapping.find(e.id);
        if (comp == componentMapping.end())
        {
            Logger::Warn("you are accessing something that is not exist");
            return nullptr;
        }
        return &components[comp->second];
    }

    void RemoveEntity(const Entity& e) override
    {
        RemoveComponent(e);
    }
};
#endif
