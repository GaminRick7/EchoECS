#pragma once
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <ostream>

#include "ComponentArray.h"

class ComponentManager {
public:
    template <typename T>
    void registerComponent()
    {
        const char * componentName = typeid(T).name();
        assert(!m_componentTypes.contains(componentName) && "Cannot register component more than once");
        m_componentTypes.insert({componentName, m_nextComponentType++});
        m_componentArrays.insert({componentName, std::make_unique<ComponentArray<T>>()});
    }

    template <typename T>
    T& getComponent(Entity e)
    {
        assert(m_componentTypes.contains(typeid(T).name()));
        return getComponentArray<T>()->getComponent(e);
    }

    template <typename T>
    void addComponent(Entity e, T component)
    {
        assert(m_componentTypes.contains(typeid(T).name()));
        getComponentArray<T>()->addComponent(e, component);
    }

    template <typename T>
    void removeComponent(Entity e)
    {
        assert(m_componentTypes.contains(typeid(T).name()));
        getComponentArray<T>()->removeComponent(e);
    }

    template <typename T>
    ComponentType getComponentType()
    {
        assert(m_componentTypes.contains(typeid(T).name()));
        // std::cout << typeid(T).name() << std::endl;
        // std::cout << (int) m_componentTypes[typeid(T).name()] << std::endl;
        return m_componentTypes[typeid(T).name()];
    }

    void EntityDestroyed(Entity e)
    {
        for (const auto& arr : m_componentArrays)
        {
            (arr.second)->EntityDestroyed(e);
        }
    }
    void printAllComponents()
    {
        for (const auto& arr : m_componentArrays)
        {
            (arr.second)->print();
        }
    }


private:
    // components types are integers (used for component mask)
    //map of component type to component type array
    std::unordered_map<const char*, std::unique_ptr<IComponentArray>> m_componentArrays;
    std::unordered_map<const char*, ComponentType> m_componentTypes;
    ComponentType m_nextComponentType{};

    template <typename T>
    ComponentArray<T>* getComponentArray()
    {
        const char * componentName = typeid(T).name();
        assert(m_componentTypes.contains(componentName));
        return static_cast<ComponentArray<T>*>(m_componentArrays[componentName].get());
    }
};
