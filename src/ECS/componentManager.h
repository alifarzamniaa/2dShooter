#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER
#include "component.h"
#include <memory>
#include <typeindex>
#include <unordered_map>

class ComponentManager
{
  public:
    template<typename T>
    void RegisterComponent()
    {
        auto c = componentsMap.find(typeid(T));
        if (c == componentsMap.end())
        {
            componentsMap[typeid(T)] = std::make_unique<ComponentContainer<T>>();
        }
    }

    template<typename T>
    void AddEntityComponent(T in_component, const Entity& e)
    {
        auto c = componentsMap.find(typeid(T));
        if (c != componentsMap.end())
        {
            static_cast<ComponentContainer<T>*>(c->second.get())->AddComponent(std::move(in_component), e);
            entityComponentsMap[e.id].push_back(typeid(T));
        }
    }

    template<typename T>
    void RemoveEntityComponent(const Entity& e)
    {
        auto c = componentsMap.find(typeid(T));
        if (c != componentsMap.end())
        {
            static_cast<ComponentContainer<T>*>(c->second.get())->RemoveComponent(e);
        }
    }

    void DestroyEntityComponents(const Entity& e)
    {
        auto listOfEntityComponent = entityComponentsMap.find(e.id);
        if (listOfEntityComponent != entityComponentsMap.end())
        {
            for (auto& ec : listOfEntityComponent->second)
            {
                auto c = componentsMap.find(ec);
                if (c != componentsMap.end())
                {
                    c->second->RemoveEntity(e);
                }
            }
            entityComponentsMap.erase(e.id);
        }
    }

    template<typename T>
    T* GetComponent(const Entity& e)
    {
        auto compContainer = componentsMap.find(typeid(T));
        if (compContainer != componentsMap.end())
        {
            return static_cast<ComponentContainer<T>*>(compContainer->second.get())->GetComponent(e);
        }
        return nullptr;
    }

  private:
    std::unordered_map<std::type_index, std::unique_ptr<ComponentI>> componentsMap;
    std::unordered_map<size_t, std::vector<std::type_index>> entityComponentsMap;
};
#endif
